#ifndef COLAPRIORIDADMIN_H_
#define COLAPRIORIDADMIN_H_

#include <stddef.h>
#include <iostream>
#include <cassert>

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
        void buscarPadreDesencolar();

        //
        void siftUp(Nodo*);

        void siftDown(Nodo*);

        bool tieneQueBajar(Nodo*);
        void swap(Nodo*);
        void liberar(Nodo*);

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
  if (false && raiz_ != NULL) {
    liberar(raiz_);
    raiz_ = NULL;
    padreParaAgregar_ = NULL;
  }
}

template <class T>
void ColaPrioridad<T>::liberar(Nodo* nodo) {
  if (nodo->der != NULL) {
    liberar(nodo->der);
  }
  if (nodo->izq != NULL) {
    liberar(nodo->izq);
  }
  delete nodo;
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
    assert(this->raiz_ != NULL);

    // si desencolamos la raiz, la tenemos que poner en null
    if (this->raiz_->izq == NULL){
        delete this->raiz_;
        this->raiz_ = NULL;
        padreParaAgregar_ = NULL;
        return;
    }



    // cambiamos la raiz por el ultimo elemento
    Nodo* auxRaiz = raiz_;
    if (padreParaAgregar_->der != NULL) {
      padreParaAgregar_->der->izq = raiz_->izq;
      if (padreParaAgregar_->der != raiz_->der) {
        padreParaAgregar_->der->der = raiz_->der;
      } else {
        padreParaAgregar_->der->der = NULL;
      }
      padreParaAgregar_->der->padre = NULL;
      if (raiz_->izq != NULL) {
        raiz_->izq->padre = padreParaAgregar_->der;
      }
      if (raiz_->der != NULL) {
        raiz_->der->padre = padreParaAgregar_->der;
      }
      raiz_ = padreParaAgregar_->der;
      padreParaAgregar_->der = NULL;
    } else if (padreParaAgregar_->izq != NULL) {
      if (padreParaAgregar_->izq != raiz_->izq) {
        padreParaAgregar_->izq->izq = raiz_->izq;
      } else {
        padreParaAgregar_->izq->izq = NULL;
      }
      padreParaAgregar_->izq->der = raiz_->der;
      padreParaAgregar_->izq->padre = NULL;
      if (raiz_->izq != NULL) {
        raiz_->izq->padre = padreParaAgregar_->izq;
      }
      if (raiz_->der != NULL) {
        raiz_->der->padre = padreParaAgregar_->izq;
      }
      raiz_ = padreParaAgregar_->izq;
      padreParaAgregar_->izq = NULL;
    } else {
      assert(false); // si llego aca es porque padreParaAgregar_ quedo
                     // mal en algun paso anterior
    }
    if (padreParaAgregar_ == raiz_) {
      padreParaAgregar_ = raiz_;
    }
    delete auxRaiz;

    buscarPadreDesencolar();

    // bajamos la raiz
    siftDown(raiz_);
}

template <class T>
bool ColaPrioridad<T>::tieneQueBajar(Nodo* aBajar) {
  if (aBajar->izq == NULL && aBajar->der == NULL) {
    return false;
  }
  if (aBajar->der != NULL && aBajar->der->valor < aBajar->valor) {
    return true;
  }
  return aBajar->izq->valor < aBajar->valor;
}


/************   AUXILIARES **************/


template <class T>
void ColaPrioridad<T>::swap(Nodo* nodoEvaluado) {
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

// Auxiliares de encolar
template <class T>
void ColaPrioridad<T>::siftUp(Nodo* nodoEvaluado){
  swap(nodoEvaluado);
}



template <class T>
void ColaPrioridad<T>::buscarPadreDesencolar(){

    if (this->padreParaAgregar_->izq != NULL){
        return;
    }

    Nodo* aux = this->padreParaAgregar_;

    while (aux != this->raiz_ && aux->padre->izq == aux) {
        aux = aux->padre;
    }
    //Encuentro el "punto de quiebre", ahora se que tengo que bajar
    if (aux != this->raiz_){
        aux = aux->padre->izq;
    }
    while (aux->der != NULL) {
        aux = aux->der;
    }
    if (aux->izq == NULL && aux->der == NULL) {
      aux = aux->padre;
    }
    this->padreParaAgregar_ = aux;
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
  // if padreParaAgregar_ no tiene hijos apunta al padre
  if (padreParaAgregar_->izq == NULL && padreParaAgregar_->der == NULL) {
    padreParaAgregar_ = padreParaAgregar_->padre;
  }

  Nodo* aBajar = nodoEvaluado;
  while (tieneQueBajar(aBajar)) {
    if (aBajar->der == NULL) {
      swap(aBajar->izq); // subo el nodo izquierdo
    } else if (aBajar->izq != NULL && aBajar->der != NULL) {
      if (aBajar->izq->valor < aBajar->der->valor) {
        swap(aBajar->izq);
      } else {
        swap(aBajar->der);
      }
    } else {
      assert(false); // esto nunca deberia pasar, asique explotamos
    }
  }
}


#endif
