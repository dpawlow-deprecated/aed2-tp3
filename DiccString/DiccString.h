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

                        const_Iterador(const typename Lista<T>::const_Iterador& otro);

                        bool HayMas() const;
                        
                        const T& Actual() const;

                        void Avanzar();

                        Lista<String> Siguientes();
                    private:

                        const DiccString* Dicc_;

                        const typename Lista<T>::const_Iterador it;

                        /// El constructor es privado, necesitamos el friend.
                        const_Iterador(const DiccString* dicc, const typename Lista<T>::const_Iterador iterador);

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

template <typename T>
DiccString<T>::DiccString()
    : raiz(NULL), claves(){
}

template <typename T>
void DiccString<T>::Borrar(const string& clave) {
Nodo* buscar = raiz;
Nodo* padre = raiz;
Nodo* hastaDondeEliminar = NULL;
Nodo* padreHDE = NULL;
Nat iHDE = 0;
Nat i = 0;

while (i < s.size()){
if aux→significado = NULL ∧ cantidadHijos(aux) = 1 ∧ hastaDondeEliminar = NULL then
hastaDondeEliminar ← aux
padreHDE ← padreAux
iHDE ← i - 1
else
if (cantidadHijos(aux) > 1 ∨ aux→significado = NULL) ∧ (i = longitud(s) -1) then
hastaDondeEliminar ← NULL
padreHDE ← NULL
iHDE ← 0
end if
end if
padreAux ← aux
if cantidadHijos(padreAux) > 1 ∧ i = longitud(s)-1 then
padreHDE ← padreAux
hastaDondeEliminar ← aux→hijos[ord(s[i])]
iHDE ← i
end if
aux ← aux→hijos[ord(s[i])]
i ← i+1
}
if hastaDondeEliminar = d ∧ cantidadHijos(aux) = 0 then
borrarNodo(d)
d ← NULL
end if
if cantidadHijos(aux) > 0 then
aux→significado ← NULL
else
borrarNodo(hastaDondeEliminar)
padreHDE→hijos[ord(s[iHDE])] ← NULL
end if
itLista(string) itlis ← CrearIt(d.Arbolito)
while HaySiguiente(itlis) ∧ Siguiente(itlis) = s do
Avanzar(it)
end while
if HaySiguiente(it) then
EliminarSiguiente(itlis)
end if
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
        if(nodo->siguientes == NULL){
            delete nodo;
        }else{
            for(int i = 0; i < 256; i++){
                if(nodo->siguientes[i] != NULL){
                    aux_delete(nodo->siguientes[i]);
                }
            }
            delete nodo;
        }
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


#endif