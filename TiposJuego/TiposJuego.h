#ifndef TIPOSJUEGO_H_
#define TIPOSJUEGO_H_

#include "../Modulos-CPP/aed2/TiposBasicos.h"
#include <cmath>
#include <cassert>

using namespace std;

template<class T, class K>
struct Tupla{
	T primero;
	K segundo;
	Tupla(T a, K b) : primero(a), segundo(b){}
	const T Primero()const{
		return primero;
	}
	const K Segundo()const{
		return segundo;
	}
};

typedef unsigned int Jugador;
typedef std::string Pokemon;
typedef unsigned int Nat;
struct Coordenada
{
	Nat latitud;
	Nat longitud;
	Coordenada(Nat latitud, Nat longitud) : latitud(latitud), longitud(longitud)
	{
	}
};

bool operator == (const Coordenada& c1, const Coordenada& c2){
 return c1.latitud == c2.latitud and c1.longitud == c2.longitud;
}

bool operator != (const Coordenada& c1, const Coordenada& c2){
 return not (c1 == c2);
}

Nat distanciaEuclidea(const Coordenada& c1, const Coordenada& c2){
	return sqrt((c1.latitud - c2.latitud) * (c1.latitud - c2.latitud) + (c1.longitud - c2.longitud) * (c1.longitud - c2.longitud));
}

Nat Latitud(Coordenada c1){
	return c1.latitud;
}

Nat Longitud(Coordenada c1){
	return c1.longitud;
}

Coordenada CoordenadaArriba(Coordenada c1){
	Coordenada c(c1.latitud +1, c1.longitud);
	return c;
}

Coordenada CoordenadaAbajo(Coordenada c1){
	assert(c1.latitud > 0);
	Coordenada c(c1.latitud -1, c1.longitud);
	return c;
}

Coordenada CoordenadaIzquierda(Coordenada c1){
	assert(c1.longitud > 0);
	Coordenada c(c1.latitud, c1.longitud -1);
	return c;
}

Coordenada CoordenadaDerecha(Coordenada c1){
	Coordenada c(c1.latitud, c1.longitud +1);
	return c;
}

bool TieneCoordenadaAbajo(Coordenada c1){
	return (c1.latitud > 0);
}

bool TieneCoordenadaIzquierda(Coordenada c1){
	return (c1.longitud > 0);
}

#endif