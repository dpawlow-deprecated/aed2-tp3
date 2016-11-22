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
    return this->raiz_->valor;
}

template <class T>
void ColaPrioridad<T>::encolar(const T& value){

    std::cout << "Valor encolado: " << value << '\n';

    Nodo* insertado = new Nodo(value);

    if (raiz_ == NULL){
        this->raiz_ = insertado;
        this->padreParaAgregar_ = insertado;
        return;
    }


    buscarPadreInsertar();

    std::cout << __LINE__ << '\n';

    insertado->padre = this->padreParaAgregar_;

    std::cout << __LINE__ << '\n';

    if (this->padreParaAgregar_->izq == NULL){
        this->padreParaAgregar_->izq = insertado;
    }else{
        this->padreParaAgregar_->der = insertado;
    }

    std::cout << __LINE__ << '\n';

    std::cout << (this->raiz_ == insertado) << '\n';

    while (insertado == this->raiz_ || insertado->valor < insertado->padre->valor){
        siftUp(insertado);
    }

    std::cout << __LINE__ << '\n';

    // INSERTAR ITERADOR ESTO TIENE QUE DEVOLVER ITERADOR
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
        ultimo = this->padreParaAgregar_->izq;
        this->padreParaAgregar_->izq = NULL;
    } else {
        ultimo = this->padreParaAgregar_->der;
        this->padreParaAgregar_->der = NULL;
    }

    ultimo->izq = this->raiz_->izq;
    ultimo->der = this->raiz_->der;
    this->raiz_ = ultimo;

    bool seElimina = ultimo->der->valor < ultimo->valor || ultimo->izq->valor < ultimo->valor;

    while (ultimo->der != NULL && ultimo->izq != NULL && seElimina){
        siftDown(ultimo);
    }

    delete aEliminar;

}


/************   AUXILIARES **************/


// Auxiliares de encolar
template <class T>
void ColaPrioridad<T>::siftUp(Nodo* nodoEvaluado){

    bool esRaiz = false;
    if (nodoEvaluado->padre == this->raiz_){
        esRaiz = true;
    }

    Nodo* auxPadre = nodoEvaluado->padre;
    Nodo* auxNodo = nodoEvaluado;

    auxNodo->padre = auxPadre->padre;
    if (auxPadre->izq == nodoEvaluado){

        auxNodo->izq = auxPadre;
        auxNodo->der = auxPadre->der;
    } else {

        auxNodo->der = auxPadre;
        auxNodo->izq = auxPadre->izq;
    }

    auxPadre->der = nodoEvaluado->der;
    auxPadre->izq = nodoEvaluado->izq;
    auxPadre->padre = nodoEvaluado;

    nodoEvaluado = auxNodo;

    if (esRaiz){
        this->raiz_ = nodoEvaluado;
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

        if (aux->der == NULL){
            padreParaAgregar_
        }
        aux = aux->der;
    }

    while (aux->izq != NULL) {
        aux = aux->izq;
    }

    this->padreParaAgregar_ = aux;
}


template <class T>
void ColaPrioridad<T>::siftDown(Nodo* nodoEvaluado){

    //TODO

    Nodo* aux = NULL;

    if (nodoEvaluado->padre->izq == nodoEvaluado){
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
}


#endif
