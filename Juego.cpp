#ifndef JUEGO_CPP
#define JUEGO_CPP

#include "Juego.h"
#include <iostream>

using namespace std;
using namespace aed2;


Juego::Juego(): cantidadTotPokemons(0), proximoIdJugador_(0) {
}

Juego::Juego(Mapa& m):  mapa(m), cantidadTotPokemons(0), proximoIdJugador_(0){  			//Complejidad O(ancho * alto)
													//Copiar el mapa es O(ancho * alto)
	mapaInfo = new Infocoordenada*[mapa.Alto()];
 	for (Nat i=0; i<mapa.Alto(); i++) {								//crear el arreglo mapa info O(ancho * alto)
		mapaInfo[i] = new Infocoordenada[mapa.Ancho()];						//El constructor por defecto de info coordenada tiene complejidad O(1)
	}												//Implicitamente se construyen por defecto el diccionario de pokemons O(1)
													//El vector de jugadores O(1) y la lista de pokemones de jugadores O(1)
}

Juego& Juego::operator=(const Juego& otro) {								//Complejidad: O(ancho * alto + |J| + |P| * (PC + PS))
	if(this != &otro) {
		mapa = otro.mapa;									//O(ancho * alto)
		pokemons = DiccString< pair<Nat, Nat> >(otro.pokemons);					//O(|P| * PS)
		jugadores = otro.jugadores;								//O(|J|)
		cantidadTotPokemons = otro.cantidadTotPokemons;						//O(1)
		coordenadasConPokemons = otro.coordenadasConPokemons;					//O(PS)
		pokemonesDeJugadores = otro.pokemonesDeJugadores;					//O(|P| * PC)
		proximoIdJugador_ = otro.proximoIdJugador_;						//O(1)

		if (mapaInfo != NULL) {
			for (Nat i=0; i<mapa.Alto(); i++) {
				delete [] mapaInfo[i];
			}
			delete [] mapaInfo;
		}

		mapaInfo = new Infocoordenada*[mapa.Alto()];
		for (Nat i=0; i<mapa.Alto(); i++) {
			mapaInfo[i] = new Infocoordenada[mapa.Ancho()];					//Crear el arreglo de mapa info es O(ancho * alto)
			for (Nat j=0; j < mapa.Ancho(); j++) {
				mapaInfo[i][j] = otro.mapaInfo[i][j];
			}
		}
	}
	return *this;
}


Juego::~Juego(){
	for (Nat i = 0; i<mapa.Alto(); i++) {								//Liberas toda la memoria del arreglo info coordenada
		delete [] mapaInfo[i];									//Los destructores de mapa, jugadores, Coordenadas con Pokemon
		mapaInfo[i] = NULL;									//y pokemones de jugadores se llaman implicitamente
	}
	delete [] mapaInfo;
	mapaInfo = NULL;
};


void Juego::AgregarPokemon(Pokemon p, Coordenada c){							//O(EC * log(EC) + |P|)
	//Defino el nuevo pokemon en todos lados, en el dicc y en el conjunto de coordenadas
	coordenadasConPokemons.AgregarRapido(c);							//O(1)
	if(!pokemons.Definido(p)){									//O(|p|) * 2
		pokemons.Definir(p, pair<Nat, Nat> (1, 1));
	}else{												//O(|p|) * 3
		Nat k = pokemons.Significado(p).first;
		Nat b = pokemons.Significado(p).second;
		pokemons.Definir(p, pair<Nat, Nat> (k+1, b+1));
	}
	mapaInfo[c.latitud][c.longitud].hayPokemon = true;
	ColaPrioridad< pair<Nat, Jugador> > cj;
	mapaInfo[c.latitud][c.longitud].jugEspe = cj;
	mapaInfo[c.latitud][c.longitud].yaSeCapturo = false;
	mapaInfo[c.latitud][c.longitud].movimientosRestantes = 10;
	mapaInfo[c.latitud][c.longitud].pokemon = p;

	//Luego me arma una lista con todas las coordenadas que existan cerca de la coordenada pasada por parametros y agrego a c a la lista
	Lista<Coordenada> lc;
	lc = CeldasValidas(c);										//O(1)
	cantidadTotPokemons++;

	//Recorro todas las coordenadas y por cada una, me fijo los jugadores en el radio de captura y defino sus interadores a la nueva cola
	Lista<Coordenada>::const_Iterador itcoordenadas = lc.CrearIt();
	while(itcoordenadas.HaySiguiente()){    							//O(EC * log(EC))
		if(mapa.HayCamino(itcoordenadas.Siguiente(), c)){
			Dicc<Jugador, ColaPrioridad< pair<Nat, Jugador> >::Iterador >::const_Iterador itJugadores = mapaInfo[itcoordenadas.Siguiente().latitud][itcoordenadas.Siguiente().longitud].jugadoresCoordenada.CrearIt();
			Nat cantidadClaves = mapaInfo[itcoordenadas.Siguiente().latitud][itcoordenadas.Siguiente().longitud].jugadoresCoordenada.CantClaves();
			while(cantidadClaves > 0 && itJugadores.HaySiguiente()){
				pair<Nat, Jugador> aEncolar(jugadores[itJugadores.SiguienteClave()].cantTotalPoke, itJugadores.SiguienteClave());
				ColaPrioridad< pair<Nat, Jugador> >::Iterador itCola;
				itCola = mapaInfo[c.latitud][c.longitud].jugEspe.encolar(aEncolar);

				mapaInfo[itcoordenadas.Siguiente().latitud][itcoordenadas.Siguiente().longitud].jugadoresCoordenada.Definir(itJugadores.SiguienteClave(), itCola);
				itJugadores.Avanzar();
			}
		}
		itcoordenadas.Avanzar();
	}

};

Juego::IterJugador Juego::AgregarJugador(){								//O(J)
	DiccString<Nat> dicc;
	Lista< DiccString<Nat> >::Iterador it = pokemonesDeJugadores.AgregarAtras(dicc);
	Coordenada c(0,0);
	InfoJugador i(c, it);
	i.conectado = false;
	i.expulsado = false;
	i.id = proximoIdJugador_;
	i.sanciones = 0;
	i.pos = c;
	i.cantTotalPoke = 0;

	proximoIdJugador_++;

	jugadores.AgregarAtras(i);									//O(J)
	Juego::IterJugador iter = Jugadores();
	Nat q = 0;
	while(q < jugadores.Longitud()){								//O(J)
		iter.Avanzar();
		q++;
	}
	return iter;
};

//Pre: {g =obs g0 ∧ j ∈ jugadores(g) ∧L ¬estaConectado(j, g) ∧ posExistente(c, mapa(g))}
void Juego::Conectarse(Jugador j, Coordenada c){

	jugadores[j].conectado = true;
	jugadores[j].pos = c;

	//TODO: hay que reiniciar la cantidad de movimientos restantes?

	if(HayPokemonCercano(c) && mapa.HayCamino(PosPokemonCercano(c), c)){
		jugadores[j].posicionMapa = mapaInfo[c.latitud][c.longitud].jugadoresCoordenada.DefinirRapido(j, mapaInfo[PosPokemonCercano(c).latitud][PosPokemonCercano(c).longitud].jugEspe.encolar(pair<Nat, Jugador>(jugadores[j].cantTotalPoke, j)));
		mapaInfo[PosPokemonCercano(c).latitud][PosPokemonCercano(c).longitud].movimientosRestantes = 10;
	}else{
		ColaPrioridad< pair<Nat, Jugador> >::Iterador itVacio;
		Dicc<Jugador, ColaPrioridad< pair<Nat, Jugador> >::Iterador >::Iterador itPosicion = mapaInfo[c.latitud][c.longitud].jugadoresCoordenada.DefinirRapido(j, itVacio);
		jugadores[j].posicionMapa = itPosicion;
	}
};

//TODO: revisar, creo que tiene sentido asi porque no podemos guardar NULL en las variables
void Juego::Desconectarse(Jugador j){									//O(log(EC))
	assert(jugadores[j].conectado);
	jugadores[j].conectado = false;
	if(jugadores[j].posicionMapa.HaySiguiente() && jugadores[j].posicionMapa.SiguienteSignificado().HayMas()){
		jugadores[j].posicionMapa.SiguienteSignificado().Borrar();				//O(log(EC))
	}
	if(jugadores[j].posicionMapa.HaySiguiente()) {
		jugadores[j].posicionMapa.EliminarSiguiente();						//O(1)
	}
};

void Juego::Moverse(Jugador j, Coordenada c){
	VerCapturas(j, c);
	ActualizarJugadorYcoordenada(j, c);
};

Juego::IterJugador Juego::Jugadores()const{								//O(1)
	return IterJugador(this);
};

bool Juego::EstaConectado(Jugador j){									//O(1)
	return jugadores[j].conectado;
};

Nat Juego::Sanciones(Jugador j){									//O(1)
	return jugadores[j].sanciones;
};

Coordenada Juego::Posicion(Jugador j){									//O(1)
	return jugadores[j].pos;
};

Juego::IterPokemon Juego::Pokemons(Jugador j){								//O(1)
	return IterPokemon(this, j);
};

Conj<Jugador> Juego::Expulsados(){
	typename Vector<InfoJugador>::const_Iterador it = jugadores.CrearIt();				//O(J)
	Conj<Jugador> c;
	while(it.HaySiguiente()){
		if(it.Siguiente().expulsado == true){
			c.Agregar(it.Siguiente().id);
		}
		it.Avanzar();
	}
	return c;
};

Conj<Coordenada>& Juego::PosConPokemons(){								//O(1)
	return coordenadasConPokemons;
};

Pokemon Juego::PokemonEnPos(Coordenada c){								//O(1)
	return mapaInfo[c.latitud][c.longitud].pokemon;
};

Nat Juego::CantMovimientosParaCaptura(Coordenada c){							//O(1)
	return mapaInfo[c.latitud][c.longitud].movimientosRestantes;

};

Conj<Jugador> Juego::JugadoresConectados(){
	Vector<InfoJugador>::const_Iterador it = jugadores.CrearIt();
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
	Conj<Coordenada> coordenadasConPokemons = PosConPokemons();
	Conj<Coordenada>::const_Iterador iter = coordenadasConPokemons.CrearIt();

	while (iter.HaySiguiente()){
		if (distanciaEuclidea(c, iter.Siguiente()) <= 25){
			return false;
		}
		iter.Avanzar();
	}
	return true;
};

bool Juego::HayPokemonCercano(const Coordenada c) {
	bool res = false;
	Lista<Coordenada> coordCercanas = CeldasValidas(c);
	Lista<Coordenada>::const_Iterador iter = coordCercanas.CrearIt();

	while (iter.HaySiguiente()) {
		Coordenada coordAux = iter.Siguiente();
		if (mapaInfo[coordAux.latitud][coordAux.longitud].hayPokemon == true){
			res = true;
		}
		iter.Avanzar();
	}

	return res;
};

Nat Juego::IndiceRareza(Pokemon p){
	Nat cant = pokemons.Significado(p).second;
	return 100-((cant*100)/cantidadTotPokemons);
};

Nat Juego::CantPokemonsTotales(){
	return cantidadTotPokemons;
};

Coordenada Juego::PosPokemonCercano(Coordenada c){
	Coordenada res(0 ,0);
	Lista<Coordenada> coordCercanas = CeldasValidas(c);
	Lista<Coordenada>::const_Iterador iter = coordCercanas.CrearIt();
	while (iter.HaySiguiente()){
		Coordenada coordAux = iter.Siguiente();
		if (mapaInfo[coordAux.latitud][coordAux.longitud].hayPokemon){
			res = coordAux;
		}
		iter.Avanzar();
	}
	return res;
};

Lista<Coordenada> Juego::CeldasValidas(Coordenada c){
	Lista<Coordenada> ls;
	ls.AgregarAtras(c);
	Nat i = 2;
	while(i > 0){
		ls.AgregarAtras(Coordenada(c.latitud+i, c.longitud));
		if(c.latitud>=i){
			ls.AgregarAtras(Coordenada(c.latitud-i, c.longitud));
		}
		ls.AgregarAtras(Coordenada(c.latitud, c.longitud+i));
		if(c.longitud >=i){
			ls.AgregarAtras(Coordenada(c.latitud, c.longitud-i));
		}
		i--;
	}

	i = 1;
	while(i > 0){
		ls.AgregarAtras(Coordenada(c.latitud+i, c.longitud+i));
		if(c.latitud >= i){
			ls.AgregarAtras(Coordenada(c.latitud-i, c.longitud+i));
		}
		if(c.latitud>=i && c.longitud >=i){
			ls.AgregarAtras(Coordenada(c.latitud-i, c.longitud-i));
		}
		if(c.longitud>=i){
			ls.AgregarAtras(Coordenada(c.latitud+i, c.longitud-i));
		}
		i--;
	}

	Lista<Coordenada>::Iterador it = ls.CrearIt();
	while(it.HaySiguiente()){
		if(mapa.PosExistente(it.Siguiente())){
			it.Avanzar();
		}else{
			it.EliminarSiguiente();
		}
	}

	return ls;
};

void Juego::ActualizarJugadorYcoordenada(Jugador j, Coordenada c){

	//sanciones
	if(distanciaEuclidea(c, jugadores[j].pos) > 100 || !(mapa.HayCamino(c, jugadores[j].pos))){
		jugadores[j].sanciones = jugadores[j].sanciones +1;
		if (jugadores[j].sanciones > 4){
			jugadores[j].expulsado = true;
		}
	}

	if(jugadores[j].expulsado == true){
		// restamos pokemones de pokemones totales cuando expulsamos gente
		cantidadTotPokemons = cantidadTotPokemons - jugadores[j].cantTotalPoke;
		Lista<string>::const_Iterador itPokemons = jugadores[j].pokemons.Siguiente().Claves().CrearIt();
		while(itPokemons.HaySiguiente()) {
			pokemons.Significado(itPokemons.Siguiente()).second -= jugadores[j].pokemons.Siguiente().Significado(itPokemons.Siguiente());
			itPokemons.Avanzar();
		}
		jugadores[j].pokemons.EliminarSiguiente();
		jugadores[j].cantTotalPoke = 0;
		if (jugadores[j].posicionMapa.HaySiguiente() && jugadores[j].posicionMapa.SiguienteSignificado().HayMas()) {
			jugadores[j].posicionMapa.SiguienteSignificado().Borrar();
		}
		if (jugadores[j].posicionMapa.HaySiguiente()) {
			jugadores[j].posicionMapa.EliminarSiguiente();
		}
	}else{
		// si hubo sancion no calculamos nada
		if (distanciaEuclidea(c, jugadores[j].pos) <= 100 && mapa.HayCamino(c, jugadores[j].pos)) {
			// actualizamos contadores para capturas
			if (!HayPokemonCercano(jugadores[j].pos) && !HayPokemonCercano(c)) {
				// no se hace nada en este caso
			} else if (HayPokemonCercano(jugadores[j].pos) && !HayPokemonCercano(c)) {
				Coordenada pokeCoor = PosPokemonCercano(jugadores[j].pos);
				mapaInfo[pokeCoor.latitud][pokeCoor.longitud].movimientosRestantes = 10;
			} else if (!HayPokemonCercano(jugadores[j].pos) && HayPokemonCercano(c)) {
				Coordenada pokeCoor = PosPokemonCercano(c);
				mapaInfo[pokeCoor.latitud][pokeCoor.longitud].movimientosRestantes = 10;
			} else if (PosPokemonCercano(c) != PosPokemonCercano(jugadores[j].pos)) {
				Coordenada c1 = PosPokemonCercano(c);
				Coordenada c2 = PosPokemonCercano(jugadores[j].pos);
				mapaInfo[c1.latitud][c1.longitud].movimientosRestantes = 10;
				mapaInfo[c2.latitud][c2.longitud].movimientosRestantes = 10;
			}
		}
	}



	if (distanciaEuclidea(c, jugadores[j].pos) <= 100 && mapa.HayCamino(c, jugadores[j].pos)) {
		jugadores[j].pos = c;

		if (jugadores[j].posicionMapa.HaySiguiente() && jugadores[j].posicionMapa.SiguienteSignificado().HayMas()) {
			jugadores[j].posicionMapa.SiguienteSignificado().Borrar();
		}
		if (jugadores[j].posicionMapa.HaySiguiente()) {
			jugadores[j].posicionMapa.EliminarSiguiente();
		}

		if(HayPokemonCercano(c) && mapa.HayCamino(PosPokemonCercano(c), c)){
			jugadores[j].posicionMapa = mapaInfo[c.latitud][c.longitud].jugadoresCoordenada.DefinirRapido(j, mapaInfo[PosPokemonCercano(c).latitud][PosPokemonCercano(c).longitud].jugEspe.encolar(pair<Nat, Jugador> (jugadores[j].cantTotalPoke, j)));
		}else{
			ColaPrioridad< pair<Nat, Jugador> >::Iterador itq;
			Dicc<Jugador, ColaPrioridad< pair<Nat, Jugador> >::Iterador>::Iterador itPosicion = mapaInfo[c.latitud][c.longitud].jugadoresCoordenada.DefinirRapido(j, itq);
			jugadores[j].posicionMapa = itPosicion;
		}
	}
};


void Juego::VerCapturas(Jugador j, Coordenada c){
	// si es sancionado no verificamos nada de capturas
	if(distanciaEuclidea(c, jugadores[j].pos) > 100 || !(mapa.HayCamino(c, jugadores[j].pos))){
		return;
	}

	Conj<Coordenada>::Iterador iter = coordenadasConPokemons.CrearIt();

	while (iter.HaySiguiente()){
		if (distanciaEuclidea(iter.Siguiente(), c) > 25) {
			Infocoordenada* infocoor = &mapaInfo[iter.Siguiente().latitud][iter.Siguiente().longitud];
			if (infocoor->movimientosRestantes > 0)
				infocoor->movimientosRestantes -= 1;

			if (infocoor->movimientosRestantes == 0){
				infocoor->hayPokemon = false;
				infocoor->yaSeCapturo = true;
				infocoor->movimientosRestantes = 10;
				pokemons.Significado(infocoor->pokemon).first = pokemons.Significado(infocoor->pokemon).first - 1;

				if (!infocoor->jugEspe.preguntarVacia()){
					Jugador jug = infocoor->jugEspe.proximo().second;
					jugadores[jug].cantTotalPoke++;

					if (jugadores[jug].pokemons.Siguiente().Definido(infocoor->pokemon)){
						Nat auxIncrementar = jugadores[jug].pokemons.Siguiente().Significado(infocoor->pokemon);
						auxIncrementar++;
						jugadores[jug].pokemons.Siguiente().Significado(infocoor->pokemon) = auxIncrementar;
					} else {
						jugadores[jug].pokemons.Siguiente().Definir(infocoor->pokemon, 1);
					}
				}

				iter.EliminarSiguiente();
			} else {
				iter.Avanzar();
			}
		} else {
			iter.Avanzar();
		}
	}
}

Conj<Jugador> Juego::EntrenadoresPosibles(const Coordenada& c){
	Conj<Jugador> res;
	Lista<Coordenada> coord = CeldasValidas(c);
	Lista<Coordenada>::const_Iterador itCoord = coord.CrearIt();
	while(itCoord.HaySiguiente()){
		if(mapa.HayCamino(itCoord.Siguiente(), c)){
			Dicc<Jugador, ColaPrioridad< pair<Nat, Jugador> >::Iterador >::Iterador itDicc = mapaInfo[itCoord.Siguiente().latitud][itCoord.Siguiente().longitud].jugadoresCoordenada.CrearIt();
			while(itDicc.HaySiguiente()){
				Jugador j = itDicc.SiguienteClave();
				res.Agregar(j);
				itDicc.Avanzar();
			}
		}
		itCoord.Avanzar();
	}
	return res;
}

//OPERACIONES DEL ITERADOR JUGADOR

bool Juego::IterJugador::HayMas(){
	bool b = false;
	Nat i = posicion; // evitamos preguntar si el actual esta expulsado deberiamos fijarnos uno adelante
	while(i < (*vector).Longitud() && !b){
		if((*vector)[i].expulsado == false){
			b = true;
		}
		i++;
	}
	return b;
};

void Juego::IterJugador::Avanzar(){
	Nat i = posicion+1;
	while (i < (*vector).Longitud() && (*vector)[i].expulsado == true){
		i++;
	}
	posicion = i;
}

Nat Juego::IterJugador::Actual(){
	if ((*vector)[posicion].expulsado == false) {
		return posicion;
	}
	Nat i = posicion+1;
	while (i < (*vector).Longitud() && (*vector)[i].expulsado == true){
		i++;
	}
	posicion = i;
	return posicion;
}

Lista<Nat> Juego::IterJugador::Siguientes(){
	Lista<Nat> ls;
	Nat i = posicion+1;
	while(i < (*vector).Longitud()){
		if((*vector)[i].expulsado == false){
			ls.AgregarAtras(i);
		}
		i++;
	}
	return ls;
}

//OPERACIONES DEL ITERADOR POKEMON

pair<string, Nat> Juego::IterPokemon::Actual(){
	return it.Actual();
}

bool Juego::IterPokemon::HayMas(){
	return it.HayMas();
}

void Juego::IterPokemon::Avanzar(){
	it.Avanzar();
}

Lista<string> Juego::IterPokemon::Siguientes(){
	return it.Siguientes();
}

const Mapa& Juego::MapaDeJuego() const {
	return mapa;
}

Nat Juego::CantidadMismaEspecie(const Pokemon p) const {
	return pokemons.Significado(p).second;
}

#endif
