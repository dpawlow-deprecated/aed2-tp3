#ifndef TIPOSJUEGO_H_
#define TIPOSJUEGO_H_

#include "aed2/TiposBasicos.h"
using namespace aed2;

typedef unsigned int Jugador;
typedef std::string Pokemon;
struct Coordenada
{
	Nat latitud;
	Nat longitud;
	Coordenada(Nat latitud, Nat longitud) : latitud(latitud), longitud(longitud)
	{
	}
};

inline bool operator == (const Coordenada& c1, const Coordenada& c2){
 return c1.latitud == c2.latitud and c1.longitud == c2.longitud;
}

inline bool operator != (const Coordenada& c1, const Coordenada& c2){
 return not (c1 == c2);
}

inline Coordenada coordenadaAbajo(Coordenada& otra){
	Coordenada c(otra.latitud -1, otra.longitud);
	return c;
}

inline Coordenada coordenadaIzquierda(Coordenada& otra){
	Coordenada c(otra.latitud, otra.longitud -1);
	return c;
}

inline Coordenada coordenadaDerecha(Coordenada& otra){
	Coordenada c(otra.latitud, otra.longitud +1);
	return c;
}

inline Coordenada coordenadaArriba(Coordenada& otra){
	Coordenada c(otra.latitud +1, otra.longitud);
	return c;
}

inline Nat distanciaEuclidea(const Coordenada& c1, const Coordenada& c2){
	return (c1.latitud - c2.latitud) * (c1.latitud - c2.latitud) + (c1.longitud - c2.longitud) * (c1.longitud - c2.longitud);
}

inline bool TieneCoordenadaAbajo(Coordenada& c){
	return (c.latitud > 0);
}

inline bool TieneCoordenadaIzquierda(Coordenada& c){
	return (c.longitud >0);
}

#endif
