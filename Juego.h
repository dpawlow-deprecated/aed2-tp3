#ifndef JUEGO_H
#define JUEGO_H

#include "Mapa.cpp"
#include "TiposJuego.h"
#include "DiccString.h"
#include "colaPrioridadMin.hpp"
#include "Modulos-CPP/aed2/Vector.h"
#include "Modulos-CPP/aed2/Dicc.h"
#include "Modulos-CPP/aed2/Arreglo.h"
#include <iostream>

using namespace std;
using namespace aed2;

bool operator<(pair<Nat, Jugador> p1, pair<Nat, Jugador> p2){
	return p1.first < p2.first;
}

class Juego{
friend class IterJugador;
private:
	struct InfoJugador{
		Jugador id;
		bool conectado;
		bool expulsado;
		Nat sanciones;
		Coordenada pos;
		Lista< DiccString<Nat> >::const_Iterador pokemons;
		Dicc <Nat, ColaPrioridad< pair<Nat, Jugador> >::Iterador >::const_Iterador posicionMapa;
		Nat cantTotalPoke;
	};

	struct InfoCoordenada{
		Pokemon pokemon;
		ColaPrioridad< pair<Nat, Jugador> > jugEspe;
		bool hayPokemon;
		bool yaSeCapturo;
		//Dicc<Nat, ColaPrioridad< pair<Nat, Jugador> >::Iterador > jugadores;
		Nat MovimientosRestantes;
	};


	DiccString< pair<Nat, Nat> > pokemons;
	Mapa mapa;
	Vector<InfoJugador> jugadores;
	InfoCoordenada** mapaInfo;
	Nat cantidadTotPokemons;
	Conj<Coordenada> coordenadasConPokemons;
	Lista< DiccString<Nat> > pokemonesDeJugadores;
	
	Lista<Coordenada> CeldasValidas(Coordenada);
	void ActualizarJugadorYCoordenada(Jugador, Coordenada);
	void VerCapturas(Jugador, Coordenada);

public: 
	//Declaraciones de las clases de iterador
	class IterJugador;
	class IterPokemon;
	//Crea un juego vacio pero con mapa
	Juego(Mapa);
	~Juego();
	//Agrega un pokemon p en la coordenada c, si es posible
	//pre: es una coordenada valida para agregar
	void AgregarPokemon(Pokemon, Coordenada);

	//Agrega un jugador al juego, devuelve un iterador al jugador agregado
	IterJugador AgregarJugador(Jugador);

	//Conecta a un jugador al juego en la Coordenada pasada por parametros
	//pre: el jugador debe existir en el juego, y no estar expulsado
	void Conectarse(Jugador, Coordenada);

	//Igual que la anterior pero lo desconecta
	void Desconectarse(Jugador);

	//Mueve un jugador y hace un monton mas de cosas
	//pre: jugador existe y coordenada tambien
	void Moverse(Jugador, Coordenada);

	//Devuelve el mapa donde se esta jugando
	//Mapa Mapa();

	//Devuelve los jugadores actuaes del juego (no expulsados)
	IterJugador Jugadores()const;

	//Pregunta si un jugador esta conectado
	//pre: el jugador tiene que existir
	bool EstaConectado(Jugador);

	//Devuelve las sanciones de un jugador 
	//pre: el jugador tiene que existir en el juego
	Nat Sanciones(Jugador);

	//Devuelve la posicion de un jugador
	//pre: el juegador tiene que existir en el juego
	Coordenada Posicion(Jugador);

	//Devuelve los pokemons de un jugador
	//pre: el jugador tiene que existir en el juego
	IterPokemon Pokemons(Jugador);

	//Devuelve los expulsados
	Conj<Jugador> Expulsados();

	//Devuelve las posiciones con pokemons
	Conj<Coordenada> PosConPokemons();

	//Devuelve el pokemon en la coordenada
	//pre: la coordenada tiene que existir en PosConPokemon
	Pokemon PokemonEnPos(Coordenada);

	//Devuevle los movimientos que faltan para la captura
	//pre: La coordenada tiene que existir en PosConPokemon
	Nat CantMovimientosParaCaptura(Coordenada);

	//Devuelve los jugadores conectados
	Conj<Jugador> JugadoresConectados();

	//Verifica si la coordenada pasada por parametro cumple los requisitos para tener un pokemon
	bool PuedoAgregarPokemon(Coordenada);

	//Devuelve si hay un pokemon cercano
	bool HayPokemonCercano(Coordenada);

	//Devuelve el indice de rareza del pokemon 
	Nat IndiceRareza(Pokemon);

	//Devuelve la cantidad total de pokemons del juego
	Nat CantPokemonsTotales();

	//Devuelve la coordenada del pokemon mas cercano
	Coordenada PosPokemonCercano(Coordenada);

	class IterJugador{
		
		public:
			
			bool HayMas();
			void Avanzar();
			Nat Actual();
			Lista<Nat> Siguientes();

		private:
			
			Nat posicion;

			const Vector<InfoJugador>* vector;

			IterJugador(const Juego* j){
				posicion = 0;
				vector = &j->jugadores;
			};

			friend Juego::IterJugador Juego::Jugadores()const;
	};

	class IterPokemon{
		public:
			pair<string, Nat> Actual();
			bool HayMas();
			void Avanzar();
			Lista<string> Siguientes();

		private:
			DiccString<Nat>::const_Iterador it;
			IterPokemon(const Juego* j, Jugador g){
				it = j->jugadores[g].pokemons.Siguiente().CrearIt();
			};
			friend Juego::IterPokemon Juego::Pokemons(Jugador);
	};



};

#endif 