#include "mini_test.h"
#include "Coordenada.cpp"
#include "aed2/TiposBasicos.h"

using namespace std;

void test_crearCoordenadas(){
	Coordenada c(5, 4);
	ASSERT(c.latitud == 5);
	ASSERT(c.longitud == 4);

	Coordenada c1(coordenadaAbajo(c).latitud, coordenadaAbajo(c).longitud);
	ASSERT(c.latitud == 5);
	ASSERT(c.longitud == 4);
	ASSERT(c1.latitud == 4);
	ASSERT(c1.longitud == 4);

	Coordenada c2(coordenadaArriba(c).latitud, coordenadaArriba(c).longitud);
	ASSERT(c.latitud == 5);
	ASSERT(c.longitud == 4);
	ASSERT(c2.latitud == 6);
	ASSERT(c2.longitud == 4);

	Coordenada c3(coordenadaIzquierda(c).latitud, coordenadaIzquierda(c).longitud);
	ASSERT(c.latitud == 5);
	ASSERT(c.longitud == 4);
	ASSERT(c3.latitud == 5);
	ASSERT(c3.longitud == 3);

	Coordenada c4(coordenadaDerecha(c).latitud, coordenadaDerecha(c).longitud);
	ASSERT(c.latitud == 5);
	ASSERT(c.longitud == 4);
	ASSERT(c4.latitud == 5);
	ASSERT(c4.longitud == 5);

	ASSERT(TieneCoordenadaAbajo(c));
	ASSERT(TieneCoordenadaIzquierda(c));
}

void test_distaciaEuclidea(){
	Coordenada c(3, 4);
	Coordenada c1(1, 2);
	ASSERT(distanciaEuclidea(c, c1) == 2);
}


int main(){
	RUN_TEST(test_crearCoordenadas);
	RUN_TEST(test_distaciaEuclidea);
	return 0;
}
