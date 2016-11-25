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
  c.desencolar();

  ASSERT(c.preguntarVacia());
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

    ColaPrioridad<int>::Iterador it3;
    ColaPrioridad<int>::Iterador it8;
    ColaPrioridad<int>::Iterador it5;
    ColaPrioridad<int>::Iterador it6;
    ColaPrioridad<int>::Iterador it4;
    ColaPrioridad<int>::Iterador it55;
    ColaPrioridad<int>::Iterador it20;
    ColaPrioridad<int>::Iterador it1;

    it3 = c.encolar(3);
    it8 = c.encolar(8);
    it5 = c.encolar(5);
    it6 = c.encolar(6);
    it4 = c.encolar(4);
    it55 = c.encolar(5);
    it20 = c.encolar(20);
    it1 = c.encolar(1);

    ASSERT(it3 .Siguiente() == 3 );
    ASSERT(it8 .Siguiente() == 8 );
    ASSERT(it5 .Siguiente() == 5 );
    ASSERT(it6 .Siguiente() == 6 );
    ASSERT(it4 .Siguiente() == 4 );
    ASSERT(it55.Siguiente() == 5 );
    ASSERT(it20.Siguiente() == 20);
    ASSERT(it1 .Siguiente() == 1 );

    ASSERT(c.proximo() == 1);
    it3.Borrar();
    ASSERT(c.proximo() == 1);
    it4.Borrar();
    ASSERT(c.proximo() == 1);
    it8.Borrar();
    ASSERT(c.proximo() == 1);
    it1.Borrar();
    ASSERT(c.proximo() == 5);
    it5.Borrar();
    ASSERT(c.proximo() == 5);
    it55.Borrar();
    ASSERT(c.proximo() == 6);
    it6.Borrar();
    ASSERT(c.proximo() == 20);
    it20.Borrar();
}


int main() {
    RUN_TEST(test_encolar);
    RUN_TEST(test_desencolar3);
    RUN_TEST(test_desencolar);
    RUN_TEST(test_iterador);

    return 0;
}
