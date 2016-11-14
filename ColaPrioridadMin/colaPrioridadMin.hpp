#ifndef COLAPRIORIDADMIN_H_
#define COLAPRIORIDADMIN_H_

#include <stddef.h>



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
    return this->raiz_->valor;
}

template <class T>
void ColaPrioridad<T>::encolar(const T& value){
    buscarPadreInsertar();

    Nodo* insertado = new Nodo(value);
    insertado->padre = this->padreParaAgregar_;

    if (this->padreParaAgregar_->izq == NULL){
        this->padreParaAgregar_->izq = insertado;
    }else{
        this->padreParaAgregar_->der = insertado;
    }

    while (insertado->valor < insertado->padre->valor){
        siftUp(insertado);
    }

    //TODO INSERTAR ITERADOR ESTO TIENE QUE DEVOLVER ITERADOR
}

template <class T>
void ColaPrioridad<T>::desencolar(){
    //TODO
}


/************   AUXILIARES **************/


// Auxiliares de encolar
template <class T>
void ColaPrioridad<T>::siftUp(Nodo* nodoEvaluado){

    Nodo* aux = NULL;

    if (nodoEvaluado->der->valor < nodoEvaluado->valor){
        aux->der = nodoEvaluado->der->der;
        aux->izq = nodoEvaluado->der->izq;
        aux->padre = nodoEvaluado->der;

        nodoEvaluado->der->der = nodoEvaluado->der;
        nodoEvaluado->der->izq = aux;
        nodoEvaluado->der->padre = nodoEvaluado->padre;

    }else{
        aux->der = nodoEvaluado->izq->der;
        aux->izq = nodoEvaluado->izq->izq;
        aux->padre = nodoEvaluado->izq;

        nodoEvaluado->izq->der = nodoEvaluado->der;
        nodoEvaluado->izq->izq = aux;
        nodoEvaluado->izq->padre = nodoEvaluado->padre;
    }

    nodoEvaluado = aux;
}

template <class T>
void ColaPrioridad<T>::buscarPadreInsertar(){
    //TODO
}
template <class T>
void ColaPrioridad<T>::siftDown(Nodo* nodoEvaluado){
    //TODO
}


#endif
