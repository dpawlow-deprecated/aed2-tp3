#ifndef COLA_H_
#define COLA_H_

#include "Modulos-CPP/aed2/Vector.h"

using namespace std;
using namespace aed2;

template<typename T>
class Cola {
  public:
      Cola(); // Vacia()
      ~Cola();
      void Encolar(T& elem);
      bool EsVacia() const;
      T Proximo() const;
      T Desencolar();
      Nat Tamanio() const;

  private:
      Vector<T> _elementos;
};


template<typename T>
Cola<T>::Cola() {
    _elementos = Vector<T>();
}

template<typename T>
Cola<T>::~Cola() {
    while(_elementos.Longitud() != 0) {
        _elementos.TirarUltimos(1);
    }
}

template<typename T>
void Cola<T>::Encolar(T& elem) {
    _elementos.AgregarAtras(elem);
}

template<typename T>
bool Cola<T>::EsVacia() const {
    return _elementos.Longitud() == 0;
}

template<typename T>
T Cola<T>::Proximo() const {
    return _elementos.Ultimo();
}

template<typename T>
T Cola<T>::Desencolar() {
    T aux = _elementos.Ultimo();
    _elementos.TirarUltimos(1);
    return aux;
}

template<typename T>
Nat Cola<T>::Tamanio() const {
    return _elementos.Longitud();
}

#endif
