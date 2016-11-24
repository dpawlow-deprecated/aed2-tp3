#include "Juego.h"
#include <iostream>

using namespace std;
using namespace aed2;


Juego::Juego(Mapa m){
	DiccString< pair<Nat, Nat> > ndicc;
	pokemons = ndicc;
	mapa = m;
	cantidadTotPokemons = 0;
	Vector<InfoJugador> vj;
	jugadores = vj;
	Conj<Coordenada> cc;
	coordenadasConPokemons = cc;
	Lista< DiccString<Nat> > dp;
	pokemonesDeJugadores = dp;
	
	const Conj<Coordenada> coords = m.Coordenadas();
	Conj<Coordenada>::const_Iterador iter = coords.CrearIt();
	Nat ancho = 0;
	Nat alto = 0;
	while (iter.HaySiguiente()){
		Coordenada c = iter.Siguiente();
		iter.Avanzar();
		if(Latitud(c) > alto) alto = Latitud(c);
		if(Longitud(c) > ancho) ancho = Longitud(c);
 	}
 	const Nat i = ancho;
 	const Nat j = alto;
 	mapaInfo[i][j];

}

/*
Juego::~Juego(){

};
*/

void Juego::AgregarPokemon(Pokemon p, Coordenada c){
	//Defino el nuevo pokemon en todos lados, en el dicc y en el conjunto de coordenadas
	coordenadasConPokemons.AgregarRapido(c);
	if(!pokemons.Definido(p)){
		pokemons.Definir(p, pair<Nat, Nat> (1, 1));
	}else{
		Nat k = pokemons.Significado(p).first;
		Nat b = pokemons.Significado(p).second;
		pokemons.Definir(p, pair<Nat, Nat> (k+1, b+1));
	}
	mapaInfo[Latitud(c)][Longitud(c)].hayPokemon = true;
	ColaPrioridad< pair<Nat, Jugador> > cj;
	mapaInfo[Latitud(c)][Longitud(c)].jugEspe = cj;
	mapaInfo[Latitud(c)][Longitud(c)].yaSeCapturo = false;
	mapaInfo[Latitud(c)][Longitud(c)].MovimientosRestantes = 0;
	mapaInfo[Latitud(c)][Longitud(c)].pokemon = p;
	
	//Luego me arma una lista con todas las coordenadas que existan cerca de la coordenada pasada por parametros y agrego a c a la lista
	Lista<Coordenada> lc;
	lc = CeldasValidas(c);
	lc.AgregarAtras(c);
	/*
	//Recorro todas las coordenadas y por cada una, me fijo los jugadores en el radio de captura y defino sus interadores a la nueva cola 
	Lista<Coordenada>::const_Iterador itCoordenadas = lc.CrearIt();
	while(itCoordenadas.HaySiguiente()){
		Dicc<Jugador, ColaPrioridad< pair<Nat, Jugador> >::Iterador >::const_Iterador itJugadores = mapaInfo[Latitud(itCoordenadas.Siguiente())][Longitud(itCoordenadas.Siguiente())].jugadores.CrearIt();
		while(itJugadores.HaySiguiente()){
			ColaPrioridad< pair<Nat, Jugador> >::Iterador itCola = mapaInfo[Latitud(c)][Longitud(c)].jugEspe.Encolar(jugadores[itJugadores.SiguienteClave()].cantTotPoke, itJugadores.SiguienteClave());
			itJugadores.SiguienteSignficado() = itCola;
			itJugadores.Avanzar();
		}
		itCoordenada.Avanzar();
	}
	*/
};

Juego::IterJugador Juego::AgregarJugador(Jugador j){
	DiccString<Nat> dicc;
	Lista< DiccString<Nat> >::const_Iterador it = pokemonesDeJugadores.AgregarAtras(dicc);
	InfoJugador i;
	i.conectado = false;
	i.expulsado = false;
	i.id = j;
	i.sanciones = 0;
	i.pos = Coordenada(0,0);
	i.pokemons = it;
	i.cantTotalPoke = 0;

	jugadores.AgregarAtras(i);
	Juego::IterJugador iter = Jugadores();
	Nat q = 0;
	while(q < jugadores.Longitud()){
		iter.Avanzar();
		q++;
	}
	return iter;	
};

void Juego::Conectarse(Jugador j, Coordenada c){
	
	jugadores[j].conectado = true;
	jugadores[j].pos = c;
	/*
	if(HayPokemonCercano(c)){
		Dicc<Jugador, ColaPrioridad< pair<Nat, Jugador> >::Iterador >::const_Iterador itPosicion = mapaInfo[Latitud(c)][Longitud(c)].jugadores.DefinirRapido(j, mapaInfo[posPokemonCerca(c)].jugEspe.Encolar(jugadores[j].cantTotalPoke, j));
		jugadores[j].posicionMapa = itPosicion;
	}else{
		Dicc<Jugador, ColaPrioridad< pair<Nat, Jugador> >::Iterador > itPosicion = mapaInfo[Latitud(c)][Longitud[c]].jugadores.DefinirRapido(j, NULL);
		jugadores[j].posicionMapa = itPosicion;
	}
	*/
};

void Juego::Desconectarse(Jugador j){
	/*
	jugadores[j].conectado = false;
	if(jugadores[j].posicionMapa.SiguienteSignificado() == NULL){
		jugadores[j].posicionMapa.SiguienteSignificado().Borrar(jugadores[j].posicionMapa.SiguienteSignificado());
		jugadores[j].posicionMapa.EleminarSiguiente();
		jugadores[j].posicionMapa = NULL;
	}else{
		jugadores[j].posicionMapa.EleminarSiguiente();
		jugadores[j].posicionMapa = NULL;
	}
	*/
};

void Moverse(Jugador j, Coordenada c){

};

Juego::IterJugador Juego::Jugadores()const{
	return IterJugador(this);
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
	return IterPokemon(this, j);
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
	Nat cant = pokemons.Significado(p).second;
	return (100-((cant/cantidadTotPokemons)*100));
};

Nat Juego::CantPokemonsTotales(){
	return cantidadTotPokemons;
};

Coordenada Juego::PosPokemonCercano(Coordenada){

};

Lista<Coordenada> Juego::CeldasValidas(Coordenada c){
	Lista<Coordenada> ls;
	Nat i = 4;
	while(i > 0){
		ls.AgregarAtras(Coordenada(Latitud(c)+i, Longitud(c)));
		if(Latitud(c)-i>0){
			ls.AgregarAtras(Coordenada(Latitud(c)-i, Longitud(c)));
		}
		ls.AgregarAtras(Coordenada(Latitud(c), Longitud(c)+i));
		if(Longitud(c)-i >0){
			ls.AgregarAtras(Coordenada(Latitud(c), Longitud(c)-i));
		}
		i--;
	}

	i = 3;
	while(i > 0){
		if(Longitud(c)-(i-1)>0){
			ls.AgregarAtras(Coordenada(Latitud(c)+3, Longitud(c)-(i-1)));
		}
		if(Latitud(c)-(i-1)>0){
			ls.AgregarAtras(Coordenada(Latitud(c)-(i-1), Longitud(c)+3));
		}
		if(Latitud(c)-3>0 && Longitud(c)-(i-1)){
			ls.AgregarAtras(Coordenada(Latitud(c)-3, Longitud(c)-(i-1)));
		}
		if(Latitud(c)-(i-1) >0 && Longitud(c)-3 >0){
			ls.AgregarAtras(Coordenada(Latitud(c)-(i-1), Longitud(c)-3));
		}
		if(Latitud(c)-3 > 0){
			ls.AgregarAtras(Coordenada(Latitud(c)-3, Longitud(c)+(i-1)));
		}
		if(Longitud(c)-3 > 0){
			ls.AgregarAtras(Coordenada(Latitud(c)+(i-1), Longitud(c)-3));
		}
		ls.AgregarAtras(Coordenada(Latitud(c)+3, Longitud(c)+(i-1)));
		ls.AgregarAtras(Coordenada(Latitud(c)+(i-1), Longitud(c)+3));
		ls.AgregarAtras(Coordenada(Latitud(c)+(i-1), Longitud(c)+2));
		ls.AgregarAtras(Coordenada(Latitud(c)+(i-1), Longitud(c)+1));
		if(Longitud(c)-2 > 0){
			ls.AgregarAtras(Coordenada(Latitud(c)+(i-1), Longitud(c)-2));
		}
		if(Longitud(c)-1 > 0){
			ls.AgregarAtras(Coordenada(Latitud(c)+(i-1), Longitud(c)-1));
		}
		if(Latitud(c)-(i-1) > 0 && Longitud(c)-2 >0){
			ls.AgregarAtras(Coordenada(Latitud(c)-(i-1), Longitud(c)-2));
		}
		if(Latitud(c)-(i-1)>0 && Longitud(c)-1 >0){
			ls.AgregarAtras(Coordenada(Latitud(c)-(i-1), Longitud(c)-1));
		}
		if(Latitud(c)-(i-1) > 0){
			ls.AgregarAtras(Coordenada(Latitud(c)-(i-1), Longitud(c)+2));
		}
		if(Latitud(c)-(i-1) >0){
			ls.AgregarAtras(Coordenada(Latitud(c)-(i-1), Longitud(c)+1));
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
}

//OPERACIONES DEL ITERADOR JUGADOR

bool Juego::IterJugador::HayMas(){
	bool b = false;
	Nat i = posicion;
	while(i < (*vector).Longitud() && !b){
		if((*vector)[i].expulsado == false){
			b = true;
		}
		i++;
	}
	return b;
};

void Juego::IterJugador::Avanzar(){
	bool b = false;
	Nat i = posicion;
	while (i < (*vector).Longitud() && !b){
		if((*vector)[i].expulsado == false){
			b = true;
		}
		i++;
	}
	posicion = (i-1);
}

Nat Juego::IterJugador::Actual(){
	return posicion;
}

Lista<Nat> Juego::IterJugador::Siguientes(){
	Lista<Nat> ls;
	Nat i = posicion;
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

int main(){
	return 0;
}


