#ifndef COLAPRIORIDADMIN_H_
#define COLAPRIORIDADMIN_H_

#include <stddef.h>
#include <iostream>

using namespace std;

template <typename T>
class ColaPrioridad{

    public:

        //Constructor. Genera una cola de prioridad vacía.
        ColaPrioridad();

        //Destructor. Debe dejar limpia la memoria.
        ~ColaPrioridad();

        //Chequea que la lista este vacia.
        //Es la funcion "EsVacia?()"
        const bool preguntarVacia();

        //PRE: NO es vacia
        //POST: Retorna el valor del primer elemento.
        const T& proximo();

        //Agrega un elemento.
        //PRE: el elemento no existe en la cola.
        //TODO INSERTAR ITERADOR ESTO TIENE QUE DEVOLVER ITERADOR
        void encolar(const T&);

        //Elimina el proximo elemento de la cola.
        void desencolar();

        //Elimina el elemento al que apunta el puntero del parametro
        //Deberíamos hacer esto con un iterador?
        //TODO
        //void borrar();
        private:

        //La representacion de un nodo interno.
        struct Nodo{

            //El constructor, toma el elemento al que representa el nodo.

            Nodo(const T& v);
            //El elemento al que representa.
            T valor;
            //Puntero al padre.
            Nodo* padre;
            //Puntero a la raiz del subarbol izquierdo.
            Nodo* izq;
            //Puntero a la raiz del subarbol derecho.
            Nodo* der;
        };

        //Puntero a la raíz del árbol (se representa con un heap).
        Nodo* raiz_;

        //Guardamos un puntero al nodo al que le tenemos que agregar el
        //hijo cuando encolamos.
        Nodo* padreParaAgregar_;


        //FUNCIONES AUXILIARES:

        //Actualiza el padreParaAgregar_
        void buscarPadreInsertar();

        //
        void siftUp(Nodo*);

        void siftDown(Nodo*);

        //Eliminar deberia llevar iterador o puntero a nodo?
        //void eliminar(??);



};

template <class T>
ColaPrioridad<T>::Nodo::Nodo(const T& v)
    : valor(v), padre(NULL), izq(NULL), der(NULL)
{}

template <class T>
ColaPrioridad<T>::ColaPrioridad(){
    this->raiz_ = NULL;
    this->padreParaAgregar_ = this->raiz_;
}

template <class T>
ColaPrioridad<T>::~ColaPrioridad(){
    //TODO
}

template <class T>
const bool ColaPrioridad<T>::preguntarVacia(){
    return this->raiz_ == NULL;
}

template <class T>
const T& ColaPrioridad<T>::proximo(){
   //cerr << raiz_->valor << endl;
   //if(raiz_->izq != NULL)cerr << raiz_->izq->valor << endl;
   //if(raiz_->der!=NULL)cerr << raiz_->der->valor << endl;
   return this->raiz_->valor;
}

template <class T>
void ColaPrioridad<T>::encolar(const T& value){
    Nodo* insertado = new Nodo(value);

    if (raiz_ == NULL){
        this->raiz_ = insertado;
        this->padreParaAgregar_ = insertado;
        return;
    }

    buscarPadreInsertar();

    insertado->padre = this->padreParaAgregar_;

    if (this->padreParaAgregar_->izq == NULL){
        this->padreParaAgregar_->izq = insertado;
    }else{
        this->padreParaAgregar_->der = insertado;
    }
    while (insertado != this->raiz_ && insertado->valor < insertado->padre->valor){
        siftUp(insertado);
    }
    //cerr << padreParaAgregar_->valor << endl;
    //if(padreParaAgregar_->izq != NULL)cerr << padreParaAgregar_->izq->valor << endl;
    //if(padreParaAgregar_->der != NULL)cerr << padreParaAgregar_->der->valor << endl;
    // TODO INSERTAR ITERADOR ESTO TIENE QUE DEVOLVER ITERADOR
}

template <class T>
void ColaPrioridad<T>::desencolar(){

    if (this->raiz_ == NULL){
        return;
    } else if (this->raiz_->izq == NULL){
        delete this->raiz_;
        this->raiz_ = NULL;
        return;
    }

    Nodo* ultimo = NULL;
    Nodo* aEliminar = this->raiz_;

    if (this->padreParaAgregar_->der == NULL){
        std::cout << __LINE__ << '\n';
        ultimo = this->padreParaAgregar_->izq;
        this->padreParaAgregar_->izq = NULL;
    } else {
        std::cout << __LINE__ << '\n';
        ultimo = this->padreParaAgregar_->der;
        this->padreParaAgregar_->der = NULL;
        std::cout << (ultimo->valor) << '\n';
    }
    ultimo->izq = this->raiz_->izq;
    ultimo->der = this->raiz_->der;
    this->raiz_ = ultimo;

    while ((ultimo->izq != NULL && ultimo->izq->valor <= ultimo->valor) || (ultimo->der != NULL && ultimo->der->valor <= ultimo->valor)){
        siftDown(ultimo);
    }

    delete aEliminar;

}


/************   AUXILIARES **************/


// Auxiliares de encolar
template <class T>
void ColaPrioridad<T>::siftUp(Nodo* nodoEvaluado){

  if (nodoEvaluado == raiz_) {
    return;
  }

  Nodo* sube = nodoEvaluado;
  Nodo* subePadre = nodoEvaluado->padre;
  Nodo* subeDer = nodoEvaluado->der;
  Nodo* subeIzq = nodoEvaluado->izq;

  Nodo* baja = nodoEvaluado->padre;
  Nodo* bajaPadre = nodoEvaluado->padre->padre;
  Nodo* bajaDer = nodoEvaluado->padre->der;
  Nodo* bajaIzq = nodoEvaluado->padre->izq;

  //cambio padres
  // aunque sea hijo de raiz anda
  nodoEvaluado->padre->padre = nodoEvaluado;
  nodoEvaluado->padre = bajaPadre;

  // sin importar en donde esta en el arbol
  baja->izq = subeIzq;
  baja->der = subeDer;

  if (nodoEvaluado == bajaIzq) {
    sube->izq = subePadre;
    sube->der = bajaDer;
    //
    if (bajaDer != NULL) bajaDer->padre = sube;
  } else {
    sube->izq = bajaIzq;
    sube->der = subePadre;
    //
    if (bajaIzq != NULL) bajaIzq->padre = sube;
  }

  if (subeIzq != NULL) {
    subeIzq->padre = subePadre;
  }
  if (subeDer != NULL) {
    subeDer->padre = subePadre;
  }


  if (bajaPadre != NULL && bajaPadre->izq == baja) {
    bajaPadre->izq = sube;
  }
  if (bajaPadre != NULL && bajaPadre->der == baja) {
    bajaPadre->der = sube;
  }

  //seteamos la nueva raiz
  if (baja == raiz_) {
    raiz_ = sube;
  }

  if (padreParaAgregar_ == baja) {
    padreParaAgregar_ = sube;
  } else if (padreParaAgregar_ == sube) {
    padreParaAgregar_ = baja;
  }
}


template <class T>
void ColaPrioridad<T>::buscarPadreInsertar(){

    if (this->padreParaAgregar_->der == NULL){
        return;
    }

    Nodo* aux = this->padreParaAgregar_;

    while (aux != this->raiz_ && aux->padre->der == aux) {
        aux = aux->padre;
    }
    //Encuentro el "punto de quiebre", ahora se que tengo que bajar
    if (aux != this->raiz_){
        aux = aux->padre;

        aux = aux->der;
    }
    while (aux->izq != NULL) {
        aux = aux->izq;
    }
    this->padreParaAgregar_ = aux;
}


template <class T>
void ColaPrioridad<T>::siftDown(Nodo* nodoEvaluado){
 /*
    Nodo* aux = NULL;

    if (nodoEvaluado == this->raiz_){

    } else if (nodoEvaluado->padre->izq == nodoEvaluado){
        aux->der = nodoEvaluado->padre->der;
        aux->izq = nodoEvaluado->padre;
    } else {
        aux->der = nodoEvaluado->padre;
        aux->izq = nodoEvaluado->padre->izq;
    }

    if (nodoEvaluado->padre == this->raiz_){
        aux->padre = NULL;
    } else {
        aux->padre = nodoEvaluado->padre->padre;
    }

    nodoEvaluado->padre->der = nodoEvaluado->der;
    nodoEvaluado->padre->izq = nodoEvaluado->izq;
    nodoEvaluado->padre->padre = nodoEvaluado->padre;
    nodoEvaluado = aux;
*/

    if(nodoEvaluado->izq != NULL && nodoEvaluado->izq->valor <= nodoEvaluado->valor){

        Nodo* auxBaja = nodoEvaluado;
        Nodo* auxSube = nodoEvaluado->izq;

        if(nodoEvaluado == this->raiz_){
            this->raiz_ = auxSube;
        }

        auxBaja->izq = auxSube->izq;
        auxBaja->der = auxSube->der;
        auxBaja->padre = auxSube;

        auxSube->izq = auxBaja;
        auxSube->der = nodoEvaluado->der;
        auxSube->padre = nodoEvaluado->padre;

        nodoEvaluado = auxBaja;

    } else if (nodoEvaluado->der != NULL && nodoEvaluado->der->valor <= nodoEvaluado->valor){

        Nodo* auxBaja = nodoEvaluado;
        Nodo* auxSube = nodoEvaluado->der;

        if(nodoEvaluado == this->raiz_){
            this->raiz_ = auxSube;
        }

        auxBaja->der = auxSube->der;
        auxBaja->izq = auxSube->izq;
        auxBaja->padre = auxSube;

        auxSube->der = auxBaja;
        auxSube->izq = nodoEvaluado->izq;
        auxSube->padre = nodoEvaluado->padre;

        nodoEvaluado = auxBaja;
    }

}


#endif
