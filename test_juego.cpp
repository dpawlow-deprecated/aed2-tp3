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
	g.Conectarse(j, c);
	g.Conectarse(j1, c1);
	g.Conectarse(j2, c2);
	g.Conectarse(j3, c3);
	ASSERT(g.JugadoresConectados().Cardinal()==4);
	ASSERT(g.JugadoresConectados().Pertenece(j));
	ASSERT(g.JugadoresConectados().Pertenece(j1));
	ASSERT(g.JugadoresConectados().Pertenece(j2));
	ASSERT(g.JugadoresConectados().Pertenece(j3));
	ASSERT(g.EstaConectado(j));
	ASSERT(g.EstaConectado(j1));
	ASSERT(g.EstaConectado(j2));
	ASSERT(g.EstaConectado(j3));
	ASSERT(!(g.HayPokemonCercano(c)));
	ASSERT(g.PuedoAgregarPokemon(c));
	g.Desconectarse(j);
	ASSERT(g.JugadoresConectados().Cardinal()==3);
	ASSERT(!(g.JugadoresConectados().Pertenece(j)));
	ASSERT(g.JugadoresConectados().Pertenece(j1));
	ASSERT(g.JugadoresConectados().Pertenece(j2));
	ASSERT(g.JugadoresConectados().Pertenece(j3));
	ASSERT(!(g.EstaConectado(j)));
	ASSERT((g.EstaConectado(j1)));
	ASSERT((g.EstaConectado(j2)));
	ASSERT((g.EstaConectado(j3)));
	g.Desconectarse(j1);
	g.Desconectarse(j2);
	g.Desconectarse(j3);
	ASSERT(g.JugadoresConectados().Cardinal()==0);
	ASSERT(!(g.JugadoresConectados().Pertenece(j)));
	ASSERT(!g.JugadoresConectados().Pertenece(j1));
	ASSERT(!g.JugadoresConectados().Pertenece(j2));
	ASSERT(!g.JugadoresConectados().Pertenece(j3));
	ASSERT(!(g.EstaConectado(j)));
	ASSERT(!(g.EstaConectado(j1)));
	ASSERT(!(g.EstaConectado(j2)));
	ASSERT(!(g.EstaConectado(j3)));
	g.Conectarse(j, c);
	g.Conectarse(j1, c1);
	g.Conectarse(j2, c2);
	g.Conectarse(j3, c3);
	ASSERT(g.Sanciones(j)==0);
	ASSERT(g.Sanciones(j1)==0);
	ASSERT(g.Sanciones(j2)==0);
	ASSERT(g.Sanciones(j3)==0);

	Pokemon s = "TuVieja";
	Coordenada fueraDeMapa(3,3);
	g.AgregarPokemon(s, c);
	ASSERT(g.HayPokemonCercano(c));
	ASSERT(!(g.HayPokemonCercano(fueraDeMapa)));
	ASSERT(!(g.PuedoAgregarPokemon(c1)));


}

int main(){
	RUN_TEST(test_juegoVacio);
	return 0;
}