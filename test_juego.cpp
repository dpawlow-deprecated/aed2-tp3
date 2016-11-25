#include "mini_test.h"
#include "Juego.cpp"

using namespace std;
using namespace aed2;

void test_juegoVacio(){
	Mapa m;
	Juego j(m);

	ASSERT(j.Expulsados().EsVacio());
	ASSERT(j.PosConPokemons().EsVacio());
	ASSERT(!j.Jugadores().HayMas());
	ASSERT(j.JugadoresConectados().EsVacio());
	ASSERT(j.CantPokemonsTotales() == 0);
}

void test_juegoMapa2x2(){
	Coordenada c(1, 1);
	Coordenada c1(1, 0);
	Coordenada c2(0, 1);
	Coordenada c3(0, 0);
	Mapa m;
	m.AgregarCoordenada(c);
	m.AgregarCoordenada(c1);
	m.AgregarCoordenada(c2);
	m.AgregarCoordenada(c3);
	
	//Asumo que HayCamino es simetrica
	ASSERT(m.Coordenadas().Cardinal() == 4);
	ASSERT(m.Coordenadas().Pertenece(c));
	ASSERT(m.Coordenadas().Pertenece(c1));
	ASSERT(m.Coordenadas().Pertenece(c2));
	ASSERT(m.Coordenadas().Pertenece(c3));
	ASSERT(m.HayCamino(c, c1));
	ASSERT(m.HayCamino(c, c2));
	ASSERT(m.HayCamino(c, c3));
	ASSERT(m.HayCamino(c1, c2));
	ASSERT(m.HayCamino(c1, c3));
	ASSERT(m.HayCamino(c2, c3));
	ASSERT(m.PosExistente(c));
	ASSERT(m.PosExistente(c1));
	ASSERT(m.PosExistente(c2));
	ASSERT(m.PosExistente(c3));
	ASSERT(m.Ancho() == 2);
	ASSERT(m.Alto() == 2);

	Jugador j = 1;
	Jugador j1 = 2;
	Jugador j2 = 3;
	Jugador j3 = 4;
	Juego g(m);
	g.AgregarJugador(j);
	g.AgregarJugador(j1);
	g.AgregarJugador(j2);
	g.AgregarJugador(j3);


}

int main(){
	RUN_TEST(test_juegoVacio);
	return 0;
}