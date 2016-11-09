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

    c.encolar(4);

    ASSERT(c.proximo() == 3);

    c.encolar(20);

    ASSERT(c.proximo() == 3);

    c.encolar(1);

    ASSERT(c.proximo() == 1);
 /*
    ColaPrioridad<char> cc;

   cc.encolar("d");

    ASSERT(cc.proximo() == "d");

    cc.encolar("z");

    ASSERT(cc.proximo() == "d");

    cc.encolar("g");

    ASSERT(cc.proximo() == "d");

    cc.encolar("a");

    ASSERT(cc.proximo() == "a");
*/
}

int main() {
    //RUN_TEST(test_punteros_cola_vacia);
    RUN_TEST(test_encolar);

    return 0;
}
