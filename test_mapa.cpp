#include <iostream>
#include <fstream>
#include "Mapa.cpp"
#include "mini_test.h"

using namespace std;
using namespace aed2;


void test_crearmapa() {
    Mapa m;
    ASSERT(m.Ancho() == 0);
    ASSERT(m.Alto() == 0);
}


int test_mapa() {
	RUN_TEST(test_crearmapa);
    return 0;
}

int main() {
	return test_mapa();
}
