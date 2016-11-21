#ifndef JUEGO_H
#define JUEGO_H

#include "Mapa.h"
#include "TiposJuego.h"
#include "DiccString.h"
#include "colaPrioridadMin.hpp"
#include "Modulos-CPP/aed2/Vector.h"
#include "Modulos-CPP/aed2/Dicc.h"
#include "Modulos-CPP/aed2/Arreglo.h"
#include <iostream>

using namespace std;
using namespace aed2;

class Juego{
public: 
	//Declaraciones de las clases de iterador
	class IterJugador;
	class IterPokemon;
	//Crea un juego vacio
	Juego();
	//Crea un juego vacio pero con mapa
	//Juego(Mapa);

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
	IterJugador Jugadores();

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

	Nat CantMovimientosParaCaptura(Coordenada);

	Conj<Jugador> JugadoresConectados();

	bool PuedoAgregarPokemon(Coordenada);

	bool HayPokemonCercano(Coordenada);

	Nat IndiceRareza(Pokemon);

	Nat CantPokemonsTotales();

	Coordenada PosPokemonCercano(Coordenada);

	class IterJugador{
		
		public:
			
			bool HayMas();
			void Avanzar();
			Nat Actual();
			Lista<Nat> Siguiente();

		private:
			struct InfoJugador{
				Jugador id;
				bool conectado;
				bool expulsado;
				Nat sanciones;
				Coordenada pos;
				Lista< DiccString<Nat> >::const_Iterador pokemons;
				// Dicc <Nat, > posicion mapa;
				Nat cantTotalPoke;
			};
					
			Nat posicion;

			const Vector<InfoJugador>* vector;

			IterJugador(const Juego& j);

			friend Juego::IterJugador Juego::Jugadores();
	};

	class IterPokemon{
		public:
			Tupla<string, Nat> Actual();
			bool HayMas();
			void Avanzar();
			Lista<string> Siguientes();

		private:
			DiccString<Nat>::const_Iterador it;
	};

private:
	struct InfoJugador{
		Jugador id;
		bool conectado;
		bool expulsado;
		Nat sanciones;
		Coordenada pos;
		Lista< DiccString<Nat> >::const_Iterador pokemons;
		// Dicc <Nat, > posicion mapa;
		Nat cantTotalPoke;
	};

	struct InfoCoordenada{
		Pokemon pokemon;
		// ColaPrioridad<> jugEspe;
		bool hayPokemon;
		bool yaSeCapturo;
		//Dicc<Nat, > jugadores;
		Nat MovimientosRestantes;
	};


	DiccString< Tupla<Nat, Nat> > pokemons;
	//Mapa mapa;
	Vector<InfoJugador> jugadores;
	//Arreglo(infoCoordenada) mapaInfo;
	Nat cantidadTotPokemons;
	Conj<Coordenada> coordenadasConPokemons;
	Lista< DiccString<Nat> > pokemonesDeJugadores;

};

#endif 