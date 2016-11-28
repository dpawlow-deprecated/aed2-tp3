#ifndef DICC_STRING_H_
#define DICC_STRING_H_

#include "aed2/Lista.h"
#include "aed2/Conj.h"
#include <string>
#include <iostream>
#include <cassert>
#include "TiposJuego.h"
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
                class const_Iterador {
                    public:
                        //Constructor por defecto del iterador
                        const_Iterador();
                        //Constructor por copia
                        const_Iterador(const typename DiccString<T>::const_Iterador& otro);
                        //Chequea si hay mas elementos por recorrer, obs: si esta parado en el ultimo elemento esta funcion devuelve true, recien cuando se avance
                        //la funcion devuelve false
                        bool HayMas() const;
                        //Devuelve una tupla con el elemento apuntado por el iterador
                        const pair<string, T> Actual() const;
                        //Avanza al siguiente
                        void Avanzar();
                        //devuelve todas las claves que quedan recorrer
                        Lista<string> Siguientes() const;
                    private:

                        const DiccString* Dicc_;

                        typename Lista<String>::const_Iterador it;

                        /// El constructor es privado, necesitamos el friend.
                    	const_Iterador(const DiccString<T>* dicc);

                        friend typename DiccString<T>::const_Iterador DiccString<T>::CrearIt() const;
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
    //Complejidad: O(1)
}

template <typename T>
DiccString<T>::DiccString(const DiccString& d) {
    //Elimina todos los elementos de la lista
    while(claves.Longitud() > 0){
        claves.Fin();
    }
    raiz = NULL;
    //Me creo una copia de las claves del diccionario pasado por parametros
    Lista<string> c = d.Claves();
    //Idea por cada elemento de la lista, lo defino en el diccionario y despues lo borro de la copia hasta que me quede sin elementos
    while(0 < c.Longitud()){
        Definir(c.Primero(), d.Significado(c.Primero()));
        c.Fin();
    }
    //Complejidad: O(n*|L|), siendo n las claves en el diccionario pasado por parametro y |L| la longitud de la clave mas larga
}

template <typename T>
void DiccString<T>::Borrar(const string& clave) {
    //Un buscador y el padre del buscador para recorrer el trie
    Nodo* buscar = raiz;
    Nodo* padre = raiz; //El padre del buscar

    //variables utiles para saber desde donde borrar
    Nodo* hastaDondeEliminar = NULL;
    Nodo* padreHDE = NULL;
    Nat iHDE = 0;
    //Contador para recorrer la clave
    int i = 0;
    while (i < clave.size()){
    	//Me guardo hasta donde guardar, el segundo if sirve para algunos casos en donde se recetea las variables, los casos en que el nodo actual tenga
        //mas de 1 hijo o que tenga alguna definicion
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

        //El if es para el caso particular de borra una hoja cuyo padre tiene mas de 1 hijo, la idea es que solo pasa cuando estoy casi al final de la palabra.
        //Esto sucede porque en el if anterio hastaDondeEliminar es NULL y tengo que actualizar los valores para borrarlo despues
        padre = buscar;
        if((cuenta_hijos(buscar) > 1 || buscar->definicion != NULL) && (i == clave.size()-1)){
            padreHDE = padre;
            hastaDondeEliminar = buscar->siguientes[int(clave[i])];
            iHDE = i;
        }

        buscar = buscar->siguientes[int(clave[i])];
        i = i+1;
    }
    //Caso en el que el nodo que tengo que borrar tiene hijos, por ende solo borro su significado
    if(cuenta_hijos(buscar) > 0){
    	T* muere = buscar->definicion;
        delete muere;
        buscar->definicion = NULL;
    }else{
        //Caso que tengo que borrar de la raiz, esto esta porque no tengo padre por ende se romperia el siguiente caso
    	if(hastaDondeEliminar == raiz){
    		aux_delete(hastaDondeEliminar);
    		raiz = NULL;
    	}else{
            //Caso en el que tengo que borra algun nodo intermedio
    		aux_delete(hastaDondeEliminar);
            padreHDE->siguientes[int(clave[iHDE])] = NULL;
    	}
    //La idea es usar aux_delete porque borra recursivamente bajando hasta los hijos y despues borrando el nodo en cuestion, esto es asi porque al recorrer toda
    //la clave me aseguro que no tenga otra cosa definida que se pueda romper
    }

    //Luego busco la clave que hay que borrar de la lista claves
    typename Lista<string>::Iterador itlis = claves.CrearIt();
    while(itlis.HaySiguiente() && itlis.Siguiente() != clave){
        itlis.Avanzar();
    }

    //Existe por requiere, luego de encontrarlo lo elimino
    //Nota: no se indefine nada si la clave no esta definida... creo :p
    if (itlis.HaySiguiente()){
        itlis.EliminarSiguiente();
    }
    //Complejidad: O(|L| + n) siendo |L| la clave mas larga y n la cantidad de claves en el diccionario
}


template <typename T>
DiccString<T>::~DiccString(){
    //Borra las claves y luego llama a aux_delete, pasado la raiz
    while(claves.Longitud()>0){
        claves.Fin();
    }
    aux_delete(raiz);
    //Complejidad: Mucho, no importa segun Algo 2 es O(1)...
}

template <class T>
void DiccString<T>::aux_delete(Nodo* nodo){
    //La idea es que, si el puntero a nodo pasado no es null, ver si tiene algun hijo. Si lo tiene se vuelve a invocar la funcion pero ahora con el hijo.
    //Luego por la "magia" de la recursion se borrar todos los hijos (con sus respectivos hijos) del puntero a nodo pasado por parametros, despues de
    //esto se borra el nodo
    if(nodo != NULL){
        for(int i = 0; i < 256; i++){
            if(nodo->siguientes[i] != NULL){
                aux_delete(nodo->siguientes[i]);
            }
        }
        delete nodo;
   }
   //Complejidad: No tengo ganas de pensar la ecuacion de recurrencia, tarda por lo menos n siendo n la cantidad de nodos
}


template <typename T>
void DiccString<T>::Definir(const string& clave, const T& significado){
    //Veo si hay raiz o no
    if(raiz == NULL){
        //Agrego la clave a las claves del dicc
        claves.AgregarAtras(clave);
        //Creo un nodo y lo asigno como raiz
        Nodo* nuevo = new Nodo;
        unsigned int i = 0;
        raiz = nuevo;
        //Recorro la raiz, si el nodo que le sigue a la clave esta definido no hago nada, sino creo un nuevo nodo y lo "encadeno" al aterior
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
        //luego una vez en la hoja (podria no serlo) le agrego el significado. Nota: como en este caso solo voy a entrar si no tengo raiz, es logico pensar
        //que no va a haber una clave en este nodo definida anteriormente, por ende no necesito borrarla
        nuevo->definicion = new T(significado);
    }else{
        claves.AgregarAtras(clave);
        //Veo si la clave ya estaba definida, si no lo esta la busco y le defino algo, haciendo algo parecido a lo de arriba
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
            //Si lo esta, simplemente la busco, borro su significado anterior (si no lo hago pierdo memoria) y le asigno el nuevo significado
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
    //Complejidad: O(|L|) siendo |L| la clave mas larga, luego son asignaciones
}


template <typename T>
bool DiccString<T>::Definido(const string& clave) const{
    //Si la raiz es NULL no existe nada definido en el diccionario, por ende false para cualquier entrada
    if(raiz == NULL){
        return false;
    }else{
        //Sino recorro toda la clave
        Nodo* buscar = raiz;
        unsigned int i = 0;
        while((i < clave.size()) && (buscar->siguientes[int(clave[i])] != NULL)){
           buscar = buscar->siguientes[int(clave[i])];
           i++;
        }
        //Si la clave existe, debo poder recorrer el arbol sin encontrar ningun nodo no definido, luego chequeo si eso pasa, y si ademas la definicion del nodo
        //existe
        return (i == clave.size() && buscar->definicion != NULL);
    }
    //Complejidad: O(|L|)
}

template <typename T>
T& DiccString<T>::Significado(const string& clave) {
    //Pre: la clave existe en el dicc
    //busco la clave y returneo su definicion
    Nodo* buscar = raiz;
    unsigned int i = 0;
    while(i < clave.size()){
        buscar = buscar->siguientes[int(clave[i])];
        i++;
    }
    return *buscar->definicion;
    //Complejidad: O(|L|)
}


template <typename T>
const T& DiccString<T>::Significado(const string& clave) const {
    //Igual que la anterior
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
    //Complejidad: O(1), parte de la estructura
}


template <class T>
int DiccString<T>::cuenta_hijos(Nodo* n){
    //Simplemente cuenta los hijos del puntero pasado por parametros
    int j = 0;
    for(int i = 0; i < 256; i++){
        if(n->siguientes[i] != NULL){
            j++;
        }
    }
    return j;
    //Complejidad: O(1), la cantidad de los hijos es constante, como mucho tengo 256 hijos
}

template <class T>
typename DiccString<T>::const_Iterador DiccString<T>::CrearIt()const{
    //Devuelve un iterador al diccionario
	return const_Iterador(this);
    //Complejidad: O(1)
}

//OPERACIONES DEL ITERADOR
//Los 3 constructores
template <class T>
DiccString<T>::const_Iterador::const_Iterador() :
	Dicc_(NULL), it(){};

template <class T>
DiccString<T>::const_Iterador::const_Iterador(const DiccString<T>* dicc) :
	Dicc_(dicc), it(dicc->claves.CrearIt()){};

template <typename T>
DiccString<T>::const_Iterador::const_Iterador(const typename DiccString<T>::const_Iterador& otro)
  : Dicc_(otro.Dicc_), it(otro.it){};

template <class T>
bool DiccString<T>::const_Iterador::HayMas()const{
    //Llama al hay siguiente de lista
	return it.HaySiguiente();
    //O(1)
}

template <class T>
const pair<string, T> DiccString<T>::const_Iterador::Actual()const{
    //Crea un tupla y la devuelve por copia, si el tipo T es una estructura, esto esta como el orto (siempre vamos a usar tipos basicos)
	pair<string, T> t(it.Siguiente(), (*Dicc_).Significado(it.Siguiente()));
    return t;
    //O(|L|) porque tengo que buscar el significado en el diccionario
}


template <class T>
void DiccString<T>::const_Iterador::Avanzar(){
    //LLama al avanzar de lista
	it.Avanzar();
    //Complejidad: O(1)
}

template <class T>
Lista<string> DiccString<T>::const_Iterador::Siguientes()const{
    //Me creo una lista y recorro todas las claves que me quedan y devuelvo la lista. Nota: Aca vale devolver las cosas por copia porque estaria devolviendo
    //una estructura llena de string
	typename Lista<string>::const_Iterador it2 = it; //Esto funciona porque esta definido el operador asignacion en el const_Iterador de la lista
	Lista<string> l;
	while(it2.HaySiguiente()){
		l.AgregarAtras(it2.Siguiente());
		it2.Avanzar();
	}
	return l;
    //Complejidad: O(n) siendo n la cantidad de claves que quedan recorrer
}

#endif
