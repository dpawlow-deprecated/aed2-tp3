#ifndef DICC_STRING_H_
#define DICC_STRING_H_

#include "../Modulos-CPP/aed2/Lista.h"
#include "../Modulos-CPP/aed2/Conj.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;
using namespace aed2;

template<typename T>
class DiccString {
        public:
                //Declaracion de las clase definida abajo
                class const_Iterador;

                //Constructor del Dicc vacio (Operacion Vacio())
                DiccString();
                DiccString(const DiccString<T>&);
                //Destruye todos los elementos del diccionario
                ~DiccString();

                //Define una nueva clave en el diccionario, si la clave ya existia reemplaza el significado por el pasado por parametro
                void Definir(const string& clave, const T& significado);

                //Verifica si una clave esta definida en el diccionario
                bool Definido(const string& clave) const;

                //Chequea que el diccionario esta vacio
                bool Vacio();

                //Devuelve el significado de la clave 
                const T& Significado(const string& clave) const;
                T& Significado(const string& clave);

                //Borra un elemento del diccionario
                void Borrar(const string& clave);

                //Devuelve las claves definidas en el diccionario
                const Lista<string>& Claves() const;
                
                //Crea un iterador al principio del diccionario
                const_Iterador CrearIt() const;

                //Clase de const_iterador, no modificable
                class const_Iterador{
                    public:

                        const_Iterador();

                        const_Iterador(const typename DiccString<T>::const_Iterador& otro);

                        bool HayMas() const;
                        
                        const T& Actual() const;

                        void Avanzar();

                        Lista<String> Siguientes() const;
                    private:

                        const DiccString* Dicc_;

                        const typename Lista<T>::const_Iterador it;

                        /// El constructor es privado, necesitamos el friend.
                        const_Iterador(const DiccString<T>* dicc, const typename Lista<T>::const_Iterador it);

                        friend typename DiccString::const_Iterador DiccString::CrearIt() const;
                };

        private:
                struct Nodo{
                    Nodo** siguientes;
                    T* definicion;
                    Nodo(){
						siguientes = new Nodo*[256];
                        for (int i = 0; i < 256; i++){
                            siguientes[i] = NULL;
                        }
                        definicion = NULL;
                    }
                    ~Nodo(){
                        delete definicion;
						delete [] siguientes;
                    }
                };
                int cuenta_hijos(Nodo* n);
                void aux_delete(Nodo*);
                Nodo* raiz;
                Lista<string> claves;
                
};

//OPERACIONES DEL TRIE

template <typename T>
DiccString<T>::DiccString()
    : raiz(NULL), claves(){
}

template <typename T>
DiccString<T>::DiccString(const DiccString& d) {
    while(claves.Longitud() > 0){
        claves.Fin();
    }
    raiz = NULL;
    Lista<string> c = d.Claves();
    while(0 < c.Longitud()){
        Definir(c.Primero(), d.Significado(c.Primero()));
        c.Fin();
    }
}

template <typename T>
void DiccString<T>::Borrar(const string& clave) {
    //Un buscador y el padre del buscador para recorrer el trie
    Nodo* buscar = raiz;    
    Nodo* padre = raiz;
    
    //variables utiles para saber desde donde borrar
    Nodo* hastaDondeEliminar = NULL;
    Nodo* padreHDE = NULL;
    Nat iHDE = 0;
    //Contador para recorrer la clave 
    int i = 0; 
    while (i < clave.size()){
    	//Me guardo hasta donde guardar, el segundo if para algunos casos en donde se recetea las variables
        if (buscar->definicion == NULL && cuenta_hijos(buscar) <= 1 && hastaDondeEliminar == NULL) {
            hastaDondeEliminar = buscar;
            padreHDE = padre;
            iHDE = i-1;
        }else{
            if((cuenta_hijos(buscar) > 1 || buscar->definicion != NULL)){
            	hastaDondeEliminar = NULL;
            	padreHDE = NULL;
            	iHDE = 0;
            }
        }
        
        //El if es para el caso particular de borra una hoja cuyo padre tiene mas de 1 hijo
        padre = buscar;
        if((cuenta_hijos(buscar) > 1 || buscar->definicion != NULL) && (i == clave.size()-1)){
            padreHDE = padre;
            hastaDondeEliminar = buscar->siguientes[int(clave[i])];
            iHDE = i;
        }
        
        buscar = buscar->siguientes[int(clave[i])];
        i = i+1;
    }
    if(cuenta_hijos(buscar) > 0){
    	T* muere = buscar->definicion;
        delete muere;
        buscar->definicion = NULL;
    }else{
    	if(hastaDondeEliminar == raiz){
    		aux_delete(hastaDondeEliminar);
    		raiz = NULL;
    	}else{
    		aux_delete(hastaDondeEliminar);
            padreHDE->siguientes[int(clave[iHDE])] = NULL;
    	}
    }
    
    typename Lista<string>::Iterador itlis = claves.CrearIt();
    while(itlis.HaySiguiente() && itlis.Siguiente() != clave){
        itlis.Avanzar();
    }

    if (itlis.HaySiguiente()){
        itlis.EliminarSiguiente();
    }
}


template <typename T>
DiccString<T>::~DiccString(){
    while(claves.Longitud()>0){
        claves.Fin();
    }
    aux_delete(raiz);
}

template <class T>
void DiccString<T>::aux_delete(Nodo* nodo){
    if(nodo != NULL){
        for(int i = 0; i < 256; i++){
            if(nodo->siguientes[i] != NULL){
                aux_delete(nodo->siguientes[i]);
            }
        }
        delete nodo;     
   }
}


template <typename T>
void DiccString<T>::Definir(const string& clave, const T& significado){
    
    if(raiz == NULL){
        claves.AgregarAtras(clave);
        Nodo* nuevo = new Nodo;
        unsigned int i = 0;
        raiz = nuevo; 
        while(i<clave.size()){
            if(nuevo->siguientes[int(clave[i])] == NULL){
                Nodo* nuevo2 = new Nodo;
                nuevo->siguientes[int(clave[i])] = nuevo2;
                nuevo = nuevo->siguientes[int(clave[i])] ;
                i++;
            }else{
                nuevo = nuevo->siguientes[int(clave[i])];
                i++;
            }
        }
        nuevo->definicion = new T(significado);
    }else{
        claves.AgregarAtras(clave);
        if(!Definido(clave)){
            Nodo* buscar = raiz;
            unsigned int i = 0;
            while(i<clave.size()){
                if(buscar->siguientes[int(clave[i])] == NULL){
                    Nodo* nuevo2 = new Nodo;
                    buscar->siguientes[int(clave[i])] = nuevo2;
                    buscar = buscar->siguientes[int(clave[i])] ;
                    i++;
                }else{
                    buscar = buscar->siguientes[int(clave[i])];
                    i++;
                }
            }
            buscar->definicion = new T(significado);
        }else{
            Nodo* buscar = raiz;
            unsigned int i = 0;
            while(i < clave.size()){
                buscar = buscar->siguientes[int(clave[i])];
                i++;
            }
            T* borrar = buscar->definicion;
            buscar->definicion = new T(significado);
            delete borrar;
        }
    }
}


template <typename T>
bool DiccString<T>::Definido(const string& clave) const{
    if(raiz == NULL){
        return false;
    }else{
        Nodo* buscar = raiz;
        unsigned int i = 0;
        while((i < clave.size()) && (buscar->siguientes[int(clave[i])] != NULL)){
           buscar = buscar->siguientes[int(clave[i])];
           i++;
        }

        return (i == clave.size() && buscar->definicion != NULL);
    }
}

template <typename T>
T& DiccString<T>::Significado(const string& clave) {
    Nodo* buscar = raiz;
    unsigned int i = 0;
    while(i < clave.size()){
        buscar = buscar->siguientes[int(clave[i])];
        i++;
    }
    return *buscar->definicion;
}


template <typename T>
const T& DiccString<T>::Significado(const string& clave) const {
    Nodo* buscar = raiz;
    unsigned int i = 0;
    while(i < clave.size()){
        buscar = buscar->siguientes[int(clave[i])];
        i++;
    }
    return *buscar->definicion;
}


template <typename T>
const Lista<string>& DiccString<T>::Claves() const{
    return claves;
}


template <class T>
int DiccString<T>::cuenta_hijos(Nodo* n){
    int j = 0; 
    for(int i = 0; i < 256; i++){
        if(n->siguientes[i] != NULL){
            j++;
        }
    }
    return j;
}

template <class T>
typename DiccString<T>::const_Iterador DiccString<T>::CrearIt()const{
	return const_Iterador(this, claves.CrearIt());
}

//OPERACIONES DEL ITERADOR
template <class T>
DiccString<T>::const_Iterador::const_Iterador() :
	Dicc_(NULL), it(NULL){};

template <typename T>
DiccString<T>::const_Iterador::const_Iterador(const typename DiccString<T>::const_Iterador& otro)
  : Dicc_(otro.Dicc_), it(otro.it){};

template <class T>
bool DiccString<T>::const_Iterador::HayMas()const{
	return it.HaySiguiente();
}

/*
template <class T>
const T& DiccString<T>::const_Iterador::Actual()const{
	return it.Siguiente();
}
*/

template <class T>
void DiccString<T>::const_Iterador::Avanzar(){
	it.Avanzar();
}

template <class T>
Lista<string> DiccString<T>::const_Iterador::Siguientes()const{
	typename Lista<T>::const_Iterador it2 = it;
	Lista<string> l;
	while(it2.HaySiguiente()){
		l.AgregarAtras(it2.Siguiente());
		it2.Avanzar();
	}
	return l;
}

#endif