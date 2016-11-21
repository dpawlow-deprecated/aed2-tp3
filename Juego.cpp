#include "Juego.h"
#include <iostream>

using namespace std;
using namespace aed2;

/*
Juego::Juego(Mapa m){
	
};
*/

void Juego::AgregarPokemon(Pokemon p, Coordenada c){

};
/*
Juego::IterJugador Juego::AgregarJugador(Jugador j){
	DiccString<Nat> d;
	Coordenada c(0,0);
	Lista< DiccString<Nat> >::Iterador it = pokemonesDeJugadores.AgregarAtras(d);
	InfoJugador i;
	i.id = j;
	i.conectado = false;
	i.expulsado = false;
	i.pos = c;
	i.sanciones = 0;
	i.pokemons = it;
	i.cantTotalPoke = 0;
	jugadores.AgregarAtras(i);
};
*/
void Juego::Conectarse(Jugador j, Coordenada c){
	jugadores[j].conectado = true;
	jugadores[j].pos = c;
};

void Juego::Desconectarse(Jugador j){
	jugadores[j].conectado = false;
};

void Moverse(Jugador j, Coordenada c){

};

Juego::IterJugador Juego::Jugadores(){

};

bool Juego::EstaConectado(Jugador j){
	return jugadores[j].conectado;
};

Nat Juego::Sanciones(Jugador j){
	return jugadores[j].sanciones;
};

Coordenada Juego::Posicion(Jugador j){
	return jugadores[j].pos;
};

Juego::IterPokemon Juego::Pokemons(Jugador j){

};

Conj<Jugador> Juego::Expulsados(){
	typename Vector<InfoJugador>::const_Iterador it = jugadores.CrearIt();
	Conj<Jugador> c;
	while(it.HaySiguiente()){
		if(it.Siguiente().expulsado == true){
			c.Agregar(it.Siguiente().id);
		}
		it.Avanzar();
	}	
	return c;
};

Conj<Coordenada> Juego::PosConPokemons(){
	return coordenadasConPokemons;
};

Pokemon Juego::PokemonEnPos(Coordenada c){

};

Nat Juego::CantMovimientosParaCaptura(Coordenada c){

};

Conj<Jugador> Juego::JugadoresConectados(){
	typename Vector<InfoJugador>::const_Iterador it = jugadores.CrearIt();
	Conj<Jugador> c;
	while(it.HaySiguiente()){
		if((it.Siguiente().conectado == true) && (it.Siguiente().expulsado == false)){
			c.Agregar(it.Siguiente().id);
		}
		it.Avanzar();
	}	
	return c;
};

bool Juego::PuedoAgregarPokemon(Coordenada c){

};

bool Juego::HayPokemonCercano(Coordenada c){

};

Nat Juego::IndiceRareza(Pokemon p){
	Nat cant = pokemons.Significado(p).Segundo();
	return (100-((cant/cantidadTotPokemons)*100));
};

Nat Juego::CantPokemonsTotales(){
	return cantidadTotPokemons;
};

Coordenada PosPokemonCercano(Coordenada){

};

int main(){
	return 0;
}


