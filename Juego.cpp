#include "Juego.h"
#include <iostream>

using namespace std;
using namespace aed2;

/*
Juego::Juego(Mapa m){
	Conj<Coordenada> coords = m.Coordenadas();
	Conj<Coordenada>::const_Iterador iter = coords.CrearIt();
	Nat ancho = 0
	Nat alto = 0
	while (iter.HaySiguiente(){
		Coordenada c = iter.Siguiente();
		iter.Avanzar();
		if(Latitud(c) > alto){ alto = Latitud(c)};
		if(Longitud(c) > ancho){ ancho = Longitud(c)};
 	}
 	infocoor ← arreglo[ancho] de arreglo[alto] de <Vacía(), Bool, Vacía(), 10>
 	res ← <Vacio(), m, Vacía(), infocoor, 0, Vacía()>
};
*/
/*
Juego::~Juego(){

};
*/

void Juego::AgregarPokemon(Pokemon p, Coordenada c){
coordenadasConPokemons.AgregarRapido(c);
if(!pokemons.Definido(p)){
	pokemons.Definir(p, pair<Nat, Nat> (1, 1));
}else{
	Nat k = pokemons.Significado(p).first;
	Nat b = pokemons.Significado(p).second;
	pokemons.Definir(p, pair<Nat, Nat> (k+1, b+1));
}

//mapaInfo[c].hayPokemon = true;
//mapaInfo[c].jugEspe = Vacio();
//mapaInfo[c].yaSeCapturo = false;
//mapaInfo[c].movimientosRestantes = 0;
//mapaInfo[c].pokemon = p;
Lista<Coordenada> lc;
lc = CeldasValidas(c);
lc.AgregarAtras(c);
Lista<Coordenada>::const_Iterador itCoordenadas = lc.CrearIt();

/*
while(itCoordenadas.HaySiguiente()){
	//itDicc(jugador, EsperandoCapturar) itJugadores ← CrearIt(g.mapaInfo[Siguiente(itCoordenadas)].jugadores)
	while(itJugadores.HaySiguiente()){
		if(itJugadores.SiguienteSignificado() == NULL){
			itJugadores.Borrar(itJugadores.SiguienteSignificado());
		}
		itColaPrioridad itCola ← Encolar(g.mapaInfo[c].jugEspe, g.jugadores[SiguienteClave(itJugadores)].cantTotPoke, SiguienteClave(itJugadores));
		SiguienteSignficado(itJugadores) ← itCola;
		Avanzar(itJugadores);
	}
	if EsVacio?(g.mapaInfo[Siguiente(itCoordena)].jugEspe) then
		g.mapaInfo[Siguiente(itCoordena)].yaSeCapturo ← false
	end if
	Avanzar(itCoordenada)

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
};

void Juego::Desconectarse(Jugador j){
	jugadores[j].conectado = false;
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


