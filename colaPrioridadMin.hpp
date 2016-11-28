#ifndef COLAPRIORIDADMIN_H_
#define COLAPRIORIDADMIN_H_

#include <stddef.h>
#include <iostream>
#include <cassert>

using namespace std;

template <typename T>
class ColaPrioridad{

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
        //Guardamos un puntero al ultimo nodo del arbol
        Nodo* ultimo_;


        //FUNCIONES AUXILIARES:
        Nodo* buscarPadreInsertar(Nodo*);
        Nodo* buscarUltimoAlDesencolar(Nodo*);


        void siftUp(Nodo*);
        void siftDown(Nodo*);

        bool tieneQueSubir(Nodo*);
        bool tieneQueBajar(Nodo*);
        void liberar(Nodo*);

        void swap(Nodo*, Nodo*);

        // este borrar es el que llama el iterador para borrar el elemento que apunta
        void borrar(Nodo*);

    public:
        class Iterador {
            public:
                //Constructor por defecto del iterador
                Iterador();
                //Constructor por copia
                Iterador(typename ColaPrioridad<T>::Iterador& otro);
                Iterador(const typename ColaPrioridad<T>::Iterador& otro);

                //Chequea si hay mas elementos por recorrer, obs: si esta parado en el ultimo elemento esta funcion devuelve true, recien cuando se avance
                //la funcion devuelve false
                bool HayMas() const;

                T Siguiente();

                // En el TP tenemos que la cola recibe un iterador para poder borrar
                // y en realidad el iterador es quien deberia saber borrarse
                void Borrar();
            private:

                ColaPrioridad<T>::Nodo* nodo_;
                ColaPrioridad<T>* cola_;

                /// El constructor es privado, necesitamos el friend.
                Iterador(ColaPrioridad<T>* cola, ColaPrioridad<T>::Nodo* nodo);

                friend class ColaPrioridad<T>;
        };
        friend class ColaPrioridad<T>::Iterador;

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
        Iterador encolar(const T&);

        //Elimina el proximo elemento de la cola.
        void desencolar();


};

template <class T>
ColaPrioridad<T>::Nodo::Nodo(const T& v)
    : valor(v), padre(NULL), izq(NULL), der(NULL)
{}

template <class T>
ColaPrioridad<T>::ColaPrioridad(){
    this->raiz_ = NULL;
    this->ultimo_ = this->raiz_;
}

template <class T>
ColaPrioridad<T>::~ColaPrioridad(){
  if (raiz_ != NULL) {
    liberar(raiz_);
    raiz_ = NULL;
    ultimo_ = NULL;
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
   return this->raiz_->valor;
}

template <class T>
typename ColaPrioridad<T>::Iterador ColaPrioridad<T>::encolar(const T& value){
    Nodo* insertado = new Nodo(value);
    ColaPrioridad<T>::Iterador it(this, insertado);

    if (raiz_ == NULL){
        raiz_ = insertado;
        ultimo_ = insertado;
        return it;
    }

    Nodo* dondeAgregar = buscarPadreInsertar(ultimo_);

    if (dondeAgregar->izq == NULL) {
        dondeAgregar->izq = insertado;
    } else if (dondeAgregar->der == NULL) {
        dondeAgregar->der = insertado;
    } else {
        assert(false); // no deberia pasar, exploto
    }
    insertado->padre = dondeAgregar;
    ultimo_ = insertado;

    siftUp(insertado);

    return it;
}

template <class T>
void ColaPrioridad<T>::desencolar(){
    assert(!preguntarVacia());

    // si desencolamos la raiz, la tenemos que poner en null
    if (raiz_->izq == NULL) {
        delete raiz_;
        raiz_ = NULL;
        ultimo_ = NULL;
        return;
    }

    Nodo* nuevoUltimo = buscarUltimoAlDesencolar(ultimo_);

    Nodo* aBorrar = raiz_;
    swap(raiz_, ultimo_); // guarda, modifica raiz_ y ultimo_ esta funcion

    // lo saco
    if (ultimo_->padre->der == aBorrar) {
      ultimo_->padre->der = NULL;
    } else if (ultimo_->padre->izq == aBorrar) {
      ultimo_->padre->izq = NULL;
    } else {
      assert(false); // no deberia pasar, reviento por los aires
    }
    delete aBorrar;

    ultimo_ = nuevoUltimo;
    siftDown(raiz_);

    return;
}

template <class T>
bool ColaPrioridad<T>::tieneQueSubir(Nodo* aSubir) {
  if (aSubir->padre == NULL) {
    return false;
  }
  return aSubir->valor < aSubir->padre->valor;
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
void ColaPrioridad<T>::swap(Nodo* nodo1, Nodo* nodo2) {
    Nodo* n1 = nodo1;
    Nodo* n1Padre = nodo1->padre;
    Nodo* n1Der = nodo1->der;
    Nodo* n1Izq = nodo1->izq;

    Nodo* n2 = nodo2;
    Nodo* n2Padre = nodo2->padre;
    Nodo* n2Der = nodo2->der;
    Nodo* n2Izq = nodo2->izq;

    //cambio padres
    if (nodo1->padre == nodo2->padre) {
      // no hacer nada, dejarlos con el mismo padre
    } else if (nodo1->padre != nodo2 && nodo2->padre != nodo1) {
      // aunque una sea raiz anda
      nodo1->padre = n2Padre;
      nodo2->padre = n1Padre;
      if (nodo1->izq != NULL) {
        nodo1->izq->padre = nodo2;
      }
      if (nodo1->der != NULL) {
        nodo1->der->padre = nodo2;
      }
      if (nodo2->izq != NULL) {
        nodo2->izq->padre = nodo1;
      }
      if (nodo2->der != NULL) {
        nodo2->der->padre = nodo1;
      }
    } else { // estan uno arriba del otro
      if (nodo2->padre == nodo1) { // nodo1 es padre de nodo2
        nodo1->padre = n2;
        nodo2->padre = n1Padre;
        if (nodo1->izq != NULL && nodo1->izq != nodo2) {
          nodo1->izq->padre = nodo2;
        }
        if (nodo1->der != NULL && nodo1->der != nodo2) {
          nodo1->der->padre = nodo2;
        }
        if (nodo2->izq != NULL) {
          nodo2->izq->padre = nodo1;
        }
        if (nodo2->der != NULL) {
          nodo2->der->padre = nodo1;
        }
      } else if (nodo1->padre == nodo2) { //nodo2 es padre de nodo1
        nodo1->padre = n2Padre;
        nodo2->padre = n1;
        if (nodo1->izq != NULL) {
          nodo1->izq->padre = nodo2;
        }
        if (nodo1->der != NULL) {
          nodo1->der->padre = nodo2;
        }
        if (nodo2->izq != NULL && nodo2->izq != nodo1) {
          nodo2->izq->padre = nodo1;
        }
        if (nodo2->der != NULL && nodo2->der != nodo1) {
          nodo2->der->padre = nodo1;
        }
      }
    }

    // apuntamos los nuevos hijos de cada nodo
    nodo1->izq = n2Izq;
    if (nodo1->izq != NULL && nodo1->izq == nodo1) { //esto pasa cuando un nodo es padre del otro
      nodo1->izq = nodo2;
    }
    nodo1->der = n2Der;
    if (nodo1->der != NULL && nodo1->der == nodo1) {
      nodo1->der = nodo2;
    }
    nodo2->izq = n1Izq;
    if (nodo2->izq != NULL && nodo2->izq == nodo2) {
      nodo2->izq = nodo1;
    }
    nodo2->der = n1Der;
    if (nodo2->der != NULL && nodo2->der == nodo2) {
      nodo2->der = nodo1;
    }

    // tenemos que actualizar las referencias de los padres
    if (nodo1->padre == nodo2->padre) {
      Nodo* izqAux = nodo1->padre->izq;
      nodo1->padre->izq = nodo1->padre->der;
      nodo1->padre->der = izqAux;
    } else {
      if (n1Padre != NULL && n1Padre->izq == n1) {
        n1Padre->izq = n2;
      }
      if (n1Padre != NULL && n1Padre->der == n1) {
        n1Padre->der = n2;
      }
      if (n2Padre != NULL && n2Padre->izq == n2) {
        n2Padre->izq = n1;
      }
      if (n2Padre != NULL && n2Padre->der == n2) {
        n2Padre->der = n1;
      }
    }

    //seteamos la nueva raiz
    if (nodo1 == raiz_) {
      raiz_ = nodo2;
    } else if (nodo2 == raiz_) {
      raiz_ = nodo1;
    }
    //actualizamos el ultimo
    if (ultimo_ == nodo1) {
      ultimo_ = nodo2;
    } else if (ultimo_ == nodo2) {
      ultimo_ = nodo1;
    }
}


template <class T>
void ColaPrioridad<T>::siftUp(Nodo* nodoEvaluado){
    while (tieneQueSubir(nodoEvaluado)){
        swap(nodoEvaluado, nodoEvaluado->padre);
    }
}


template <class T>
typename ColaPrioridad<T>::Nodo* ColaPrioridad<T>::buscarUltimoAlDesencolar(Nodo* nodo){
    if (nodo->padre->der == nodo) {
        return nodo->padre->izq;
    }

    Nodo* aux = nodo->padre;
    while (aux != raiz_ && aux->padre->izq == aux) {
        aux = aux->padre;
    }
    //Encuentro el "punto de quiebre", ahora se que tengo que bajar
    if (aux != this->raiz_){
        aux = aux->padre->izq;
    }
    while (aux->der != NULL) {
        aux = aux->der;
    }

    return aux;
}


template <class T>
typename ColaPrioridad<T>::Nodo* ColaPrioridad<T>::buscarPadreInsertar(Nodo* nodo){
    if (nodo == raiz_) {
      return nodo;
    }
    if (nodo->padre->der == NULL){
        return nodo->padre;
    }

    Nodo* aux = nodo->padre;
    while (aux != this->raiz_ && aux->padre->der == aux) {
        aux = aux->padre;
    }
    //Encuentro el "punto de quiebre", ahora se que tengo que bajar
    if (aux != this->raiz_) {
        aux = aux->padre->der;
    }
    while (aux->izq != NULL) {
        aux = aux->izq;
    }

    return aux;
}


template <class T>
void ColaPrioridad<T>::siftDown(Nodo* nodoEvaluado) {
  Nodo* aBajar = nodoEvaluado;
  while (tieneQueBajar(aBajar)) {
    if (aBajar->der == NULL) {
      swap(aBajar->izq, aBajar); // subo el nodo izquierdo
    } else if (aBajar->izq != NULL && aBajar->der != NULL) {
      if (aBajar->izq->valor < aBajar->der->valor) {
        swap(aBajar->izq, aBajar);
      } else {
        swap(aBajar->der, aBajar);
      }
    } else {
      assert(false); // esto nunca deberia pasar, asique explotamos
    }
  }
}

template <class T>
void ColaPrioridad<T>::borrar(Nodo* nodo) {
  if (nodo == raiz_) {
    desencolar();
    return;
  }

  Nodo* ultimoOriginal = ultimo_;

  // swap actualiza raiz_ y ultimo_ por lo cual ultimo_ apunta al
  // elemento a eliminar despues de esta linea
  if (nodo != ultimo_) {
    swap(nodo, ultimo_);
  }

  Nodo* nuevoUltimo = buscarUltimoAlDesencolar(ultimo_);

  // lo saco
  if (ultimo_->padre->der == nodo) {
    ultimo_->padre->der = NULL;
  } else if (ultimo_->padre->izq == nodo) {
    ultimo_->padre->izq = NULL;
  } else {
    assert(false); // no deberia pasar, reviento por los aires
  }
  delete nodo;

  ultimo_ = nuevoUltimo;

  siftUp(ultimoOriginal);
  siftDown(ultimoOriginal);
}



//OPERACIONES DEL ITERADOR
//Los 3 constructores
template <class T>
ColaPrioridad<T>::Iterador::Iterador() :
  nodo_(NULL){};

template <class T>
ColaPrioridad<T>::Iterador::Iterador(ColaPrioridad<T>* cola, ColaPrioridad<T>::Nodo* nodo) :
  nodo_(nodo), cola_(cola){};

template <class T>
ColaPrioridad<T>::Iterador::Iterador(ColaPrioridad<T>::Iterador& otro)
  : nodo_(otro.nodo_){};

template <class T>
ColaPrioridad<T>::Iterador::Iterador(const ColaPrioridad<T>::Iterador& otro)
  : nodo_(otro.nodo_){};



template <class T>
bool ColaPrioridad<T>::Iterador::HayMas() const {
  return nodo_->izq != NULL || nodo_->der != NULL || nodo_->padre != NULL;
}

template <class T>
T ColaPrioridad<T>::Iterador::Siguiente() {
  return nodo_->valor;
}

template <class T>
void ColaPrioridad<T>::Iterador::Borrar() {
  cola_->borrar(nodo_);
}



#endif
