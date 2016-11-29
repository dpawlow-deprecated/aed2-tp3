#include <iostream>
#include <fstream>
#include "Cola.cpp"
#include "mini_test.h"

using namespace std;
using namespace aed2;


void test_crearcola() {
    Cola<Nat> c;
    ASSERT(c.EsVacia());
    ASSERT(c.Tamanio() == 0);
}

void test_5_elementos() {
    Cola<Nat> c;
    ASSERT(c.EsVacia());

    Nat t1 = 10;
    c.Encolar(t1);
    ASSERT(c.EsVacia() == false);
    ASSERT(c.Proximo() == 10);
    ASSERT(c.Tamanio() == 1);

    Nat t2 = 11;
    c.Encolar(t2);
    ASSERT(c.EsVacia() == false);
    ASSERT(c.Proximo() == 11);
    ASSERT(c.Tamanio() == 2);

    Nat t3 = 12;
    c.Encolar(t3);
    ASSERT(c.EsVacia() == false);
    ASSERT(c.Proximo() == 12);
    ASSERT(c.Tamanio() == 3);

    Nat t4 = 13;
    c.Encolar(t4);
    ASSERT(c.EsVacia() == false);
    ASSERT(c.Proximo() == 13);
    ASSERT(c.Tamanio() == 4);

    Nat t5 = 14;
    c.Encolar(t5);
    ASSERT(c.EsVacia() == false);
    ASSERT(c.Proximo() == 14);
    ASSERT(c.Tamanio() == 5);


    c.Desencolar();
    ASSERT(c.Proximo() == 13);

    c.Desencolar();
    ASSERT(c.Proximo() == 12);

    c.Desencolar();
    ASSERT(c.Proximo() == 11);

    c.Desencolar();
    ASSERT(c.Proximo() == 10);

    c.Desencolar();

    ASSERT(c.Tamanio() == 0);
    ASSERT(c.EsVacia());
}

void test_muchas_cosas() {

    Cola<Nat> c;

    for (Nat i = 1; i <= 200; i++) {
        Nat e = i;
        c.Encolar(e);
        ASSERT(c.Proximo() == e);
        ASSERT(c.Tamanio() == i);
        ASSERT(c.EsVacia() == false);
    }

    Nat n = 200;
    while (c.EsVacia() == false) {
        ASSERT(c.Proximo() == n);
        ASSERT(c.Tamanio() == n);
        c.Desencolar();
        n--;
    }

    ASSERT(c.Tamanio() == 0);
    ASSERT(c.EsVacia());
}


int test_cola() {
	RUN_TEST(test_crearcola);
	RUN_TEST(test_5_elementos);
	RUN_TEST(test_muchas_cosas);
    return 0;
}

int main() {
	return test_cola();
}
