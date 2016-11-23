#include <iostream>
#include "mini_test.h"

#include "colaPrioridadMin.hpp"

//void test_punteros_cola_vacia(){
//    ColaPrioridad<int> c;

//    ASSERT(c.raiz_ == NULL);
//    ASSERT(c.padreParaAgregar_ == NULL);

//    c.encolar(2);
//    ASSERT(c.raiz_->valor == 2);
//    ASSERT(c.raiz_->padre == NULL);
//    ASSERT(c.padreParaAgregar_->valor == NULL);
//}

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

void test_desencolar(){
    ColaPrioridad<int> c;

    c.encolar(3);
    ASSERT(c.proximo() == 3);

    c.encolar(8);
    ASSERT(c.proximo() == 3);

    c.encolar(5);
    ASSERT(c.proximo() == 3);

    c.encolar(6);
    ASSERT(c.proximo() == 3);

    c.encolar(7);
    ASSERT(c.proximo() == 3);

    c.encolar(5);
    ASSERT(c.proximo() == 3);

    c.encolar(20);
    ASSERT(c.proximo() == 3);

    c.encolar(1);
    ASSERT(c.proximo() == 1);

    std::cout << __LINE__ << '\n';

    c.desencolar();
    ASSERT(c.proximo() == 3);

    std::cout << __LINE__ << '\n';

    c.desencolar();
    ASSERT(c.proximo() == 5);

    std::cout << __LINE__ << '\n';

    c.desencolar();
    ASSERT(c.proximo() == 5);

    std::cout << __LINE__ << '\n';

    c.desencolar();
    ASSERT(c.proximo() == 6);

    std::cout << __LINE__ << '\n';

    c.desencolar();
    ASSERT(c.proximo() == 7);

    std::cout << __LINE__ << '\n';

    c.desencolar();
    ASSERT(c.proximo() == 8);

    std::cout << __LINE__ << '\n';

    c.desencolar();
    ASSERT(c.proximo() == 20);

}


int main() {
    //RUN_TEST(test_punteros_cola_vacia);
    RUN_TEST(test_encolar);
    //RUN_TEST(test_desencolar);

    return 0;
}
