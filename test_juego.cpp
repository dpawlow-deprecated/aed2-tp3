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
	//test para mapa
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

	//Test de los jugadores de mapa
	//nota: en este mapa no se pueden producir capturas, es muy pequeño
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
	ASSERT(g.Expulsados().Cardinal()==0);
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
	ASSERT(g.Posicion(j)==c);
	ASSERT(g.Posicion(j1)==c1);
	ASSERT(g.Posicion(j2)==c2);
	ASSERT(g.Posicion(j3)==c3);
	ASSERT(!g.Pokemons(j).HayMas());
	ASSERT(!g.Pokemons(j1).HayMas());
	ASSERT(!g.Pokemons(j2).HayMas());
	ASSERT(!g.Pokemons(j3).HayMas());
	Juego::IterJugador itj = g.Jugadores();
	ASSERT(itj.HayMas() && itj.Siguiente() == j);
	itj.Avanzar();
	ASSERT(itj.HayMas() && itj.Siguiente() == j1);
	itj.Avanzar();
	ASSERT(itj.HayMas() && itj.Siguiente() == j2);
	itj.Avanzar();
	ASSERT(itj.HayMas() && itj.Siguiente() == j3);
	itj.Avanzar();
	ASSERT(!itj.HayMas());

	//Test de pokemon, solo se puede agregar un pokemon
	Pokemon s = "TuVieja";
	Coordenada fueraDeMapa(3,3);
	g.AgregarPokemon(s, c);
	ASSERT(g.HayPokemonCercano(c));
	ASSERT(!(g.HayPokemonCercano(fueraDeMapa)));
	ASSERT(!(g.PuedoAgregarPokemon(c1)));
	ASSERT(g.PosConPokemons().Cardinal() == 1);
	ASSERT(g.PosConPokemons().Pertenece(c));
	ASSERT(g.PokemonEnPos(c) == s);
	ASSERT(g.CantMovimientosParaCaptura(c)==0);
	ASSERT(g.CantPokemonsTotales()==1);
	ASSERT(g.IndiceRareza(s)==0);
	ASSERT(g.PosPokemonCercano(c1) == c);
	ASSERT(g.PosPokemonCercano(c2) == c);
	ASSERT(g.PosPokemonCercano(c3) == c);

}

int main(){
	RUN_TEST(test_juegoVacio);
	RUN_TEST(test_juegoMapa2x2);
	return 0;
}
