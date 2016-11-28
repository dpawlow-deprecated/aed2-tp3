#include "Driver.h"
#include "Juego.cpp"
#include "TiposJuego.h"
#include "Coordenada.cpp"
#include "aed2.h"

using namespace std;
using namespace aed2;

// Instanciar un mapa y un juego

Driver::Driver(const Conj< Coordenada > & cs): proximoIdJugador_(0), coordenadasMapa_(cs)
{
  Conj<Coordenada>::const_Iterador it = cs.CrearIt();
  while (it.HaySiguiente()) {
    mapa_.AgregarCoordenada(it.Siguiente());
    it.Avanzar();
  }
  juego_ = new Juego(mapa_);
}

Driver::~Driver()
{
}

void Driver::agregarPokemon(const Pokemon & p, const Coordenada & c)
{
  juego_->AgregarPokemon(p, c);
}


Jugador Driver::agregarJugador() {
  juego_->AgregarJugador();
  proximoIdJugador_++;
  return proximoIdJugador_ - 1;
}

void Driver::conectarse(const Jugador & j, const Coordenada & c) {
  juego_->Conectarse(j, c);
}

void Driver::desconectarse(const Jugador & j) {
  juego_->Desconectarse(j);
}

void Driver::moverse(const Jugador & j, const Coordenada & c) {

}

Conj< Coordenada > Driver::mapa() const{
  Conj<Coordenada> out(coordenadasMapa_);
  return out;
}

/* Indica si hay un camino posible entre dos coordenadas
*  Requiere que las coordenadas existan en el mapa */
bool Driver::hayCamino(const Coordenada & c1, const Coordenada & c2) const{

}

/* Indica si una coordenada existe o no en el mapa */
bool Driver::posExistente(const Coordenada & c) const{

}

/* Devuelve los jugadores que fueron insertados en el juego y no fueron eliminados. */
Conj< Jugador > Driver::jugadores() const{

}

/* Dado el jugador pasado como parametro, retorna si esta conectado o no.
 * Requiere que el jugador este entre jugadores() del juego. */
bool Driver::estaConectado(const Jugador & j) const{

}

/* Dado el jugador pasado como parametro, devuelve la cantidad de sanciones que recibio.
 * Requiere que el jugador este entre jugadores() del juego. */
Nat Driver::sanciones(const Jugador & j) const{

}

/* Dado el jugador pasado como parametro, devuelve la coordenada donde se ubica.
 * Requiere que el jugador este entre jugadores() del juego y este conectado. */
Coordenada Driver::posicion(const Jugador & j) const{

}

/* Dado el jugador pasado como parametro, devuelve un MultiConjunto con los
 * pokemons que capturo.
 * Requiere que el jugador este entre jugadores() del juego. */
Dicc< Pokemon , Nat > Driver::pokemons(const Jugador & j) const{

}

/* Devuelve los jugadores que fueron expulsados del juego. */
Conj< Jugador > Driver::expulsados() const{

}

/* Devuelve todas las coordenadaes del mapa que tienen un pokemon en ella. */
Conj< Coordenada > Driver::posConPokemons() const{

}

/* Dada una coordenada del mapa, devuelve al pokemon situado en ella.
 * Es requisito que la coordenada exista en el mapa y que exista un pokemon alli. */
Pokemon Driver::pokemonEnPos(const Coordenada & c) const{

}

/* Dada una coordenada, devuelve el valor del contador de movimientos fuera del rango.
* Es requisito que en la coordenada pasada como parametro haya un pokemon. */
Nat Driver::cantMovimientosParaCaptura(const Coordenada & c) const{

}

/* Dada una coordenada cualquiera, indica si la coordenada existe en el mapa y
 * que hay un pokemon a distancia menor o igual a 5. */

bool Driver::puedoAgregarPokemon(const Coordenada & c) const{

}

/* Devuelve si hay un pokemon a distancia menor o igual a 2
 * de la Coordenada pasada como parametro. */
bool Driver::hayPokemonCercano(const Coordenada & c) const{

}

/* Dada una Coordenada, devuelve la coordenada del pokemon cercano.
 * Requiere que haya un pokemon a distancia menor o igual a 2. */
Coordenada Driver::posPokemonCercano(const Coordenada & c) const{

}

/* Devuelve todos los jugadores que esten a distancia menor o igual a 2 de
 * la coordenada indicada, que tengan un camino hasta ella.
 * Requiere que haya un pokemon a distancia menor o igual a 2 de la Coordenada. */
Conj<Jugador> Driver::entrenadoresPosibles(const Coordenada & c) const{

}

/* Devuelve el indice de rarez del pokemon pasado como parametro.
 * Requiere que haya al menos un pokemon de la especie en el juego. */
Nat Driver::indiceRareza(const Pokemon & p) const{

}

/* Devuelve la cantidad de pokemons totales en el juego. */
Nat Driver::cantPokemonsTotales() const{

}

/* Indica cuantos pokemons de la especie de unPokemon hay en pokemons. */
Nat Driver::cantMismaEspecie(const Pokemon & p) const{

}


// TODO: Completar con el resto de las implementaciones
