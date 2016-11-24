#include <iostream>
#include "mini_test.h"

#include "colaPrioridadMin.hpp"


void test_encolar(){
    ColaPrioridad<int> c;

    c.encolar(3);
    ASSERT(c.proximo() == 3);

    c.encolar(8);
    ASSERT(c.proximo() == 3);

    c.encolar(5);
    ASSERT(c.proximo() == 3);

    c.encolar(6);
    ASSERT(c.proximo() == 3);

    c.encolar(4);
    ASSERT(c.proximo() == 3);

    c.encolar(5);
    ASSERT(c.proximo() == 3);

    c.encolar(20);
    ASSERT(c.proximo() == 3);

    c.encolar(1);
    ASSERT(c.proximo() == 1);
}

void test_desencolar3() {
  ColaPrioridad<int> c;

  c.encolar(6);
  c.encolar(8);
  c.encolar(20);

  c.desencolar();
  c.desencolar();
}

void test_desencolar(){
    ColaPrioridad<int> c;

    c.encolar(3);
    c.encolar(8);
    c.encolar(5);
    c.encolar(6);
    c.encolar(4);
    c.encolar(5);
    c.encolar(20);
    c.encolar(1);

    c.desencolar();
    ASSERT(c.proximo() == 3);

    c.desencolar();
    ASSERT(c.proximo() == 4);

    c.desencolar();
    ASSERT(c.proximo() == 5);

    c.desencolar();
    ASSERT(c.proximo() == 5);

    c.desencolar();
    ASSERT(c.proximo() == 6);

    c.desencolar();
    ASSERT(c.proximo() == 8);

    c.desencolar();
    ASSERT(c.proximo() == 20);

    c.desencolar();

}

void test_iterador() {
    ColaPrioridad<int> c;
    ColaPrioridad<int>::Iterador it;

    c.encolar(3);
    c.encolar(8);
    c.encolar(5);
    c.encolar(6);
    c.encolar(4);
    c.encolar(5);
    it = c.encolar(20);
    c.encolar(1);

    ASSERT(it.Siguiente() == 20);
    it.Borrar();
    ASSERT(c.proximo() == 1);
}


int main() {
    //RUN_TEST(test_punteros_cola_vacia);
    RUN_TEST(test_encolar);
    RUN_TEST(test_desencolar3);
    RUN_TEST(test_desencolar);
    //RUN_TEST(test_iterador);

    return 0;
}
