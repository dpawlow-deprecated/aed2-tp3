#include "mini_test.h"
#include "Coordenada.cpp"

using namespace std;

void test_crearCoordenadas(){
	coordenada c(5, 4);
	ASSERT(c.Latitud() == 5);
	ASSERT(c.Longitud() == 4);

	coordenada c1 (c.coordenadaAbajo (c).Latitud(), c.coordenadaAbajo (c).Longitud());
	ASSERT(c.Latitud() == 5);
	ASSERT(c.Longitud() == 4);
	ASSERT(c1.Latitud() == 4);
	ASSERT(c1.Longitud() == 4);
	
	coordenada c2 (c.coordenadaArriba (c).Latitud(), c.coordenadaArriba (c).Longitud());
	ASSERT(c.Latitud() == 5);
	ASSERT(c.Longitud() == 4);
	ASSERT(c2.Latitud() == 6);
	ASSERT(c2.Longitud() == 4);

	coordenada c3 (c.coordenadaIzquierda (c).Latitud(), c.coordenadaIzquierda (c).Longitud());
	ASSERT(c.Latitud() == 5);
	ASSERT(c.Longitud() == 4);
	ASSERT(c3.Latitud() == 5);
	ASSERT(c3.Longitud() == 3);

	coordenada c4 (c.coordenadaDerecha (c).Latitud(), c.coordenadaDerecha (c).Longitud());
	ASSERT(c.Latitud() == 5);
	ASSERT(c.Longitud() == 4);
	ASSERT(c4.Latitud() == 5);
	ASSERT(c4.Longitud() == 5);
	
	ASSERT(c.TieneCoordenadaAbajo());
	ASSERT(c.TieneCoordenadaIzquierda());
}

void test_distaciaEuclidea(){
	coordenada c(3, 4);
	coordenada c1(1, 2);
	ASSERT(c.distanciaEuclidea(c1) == 2);
}


int main(){
	RUN_TEST(test_crearCoordenadas);
	RUN_TEST(test_distaciaEuclidea);
	return 0;
}