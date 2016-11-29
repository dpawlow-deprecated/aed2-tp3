#ifndef COORDENADA_CPP_
#define COORDENADA_CPP_

#include "TiposJuego.h"

using namespace aed2;

Coordenada coordenadaAbajo(Coordenada& otra){
	Coordenada c(otra.latitud -1, otra.longitud);
	return c;
}

Coordenada coordenadaIzquierda(Coordenada& otra){
	Coordenada c(otra.latitud, otra.longitud -1);
	return c;
}

Coordenada coordenadaDerecha(Coordenada& otra){
	Coordenada c(otra.latitud, otra.longitud +1);
	return c;
}

Coordenada coordenadaArriba(Coordenada& otra){
	Coordenada c(otra.latitud +1, otra.longitud);
	return c;
}

Nat distanciaEuclidea(const Coordenada& c1, const Coordenada& c2){
	return (c1.latitud - c2.latitud) * (c1.latitud - c2.latitud) + (c1.longitud - c2.longitud) * (c1.longitud - c2.longitud);
}

bool TieneCoordenadaAbajo(Coordenada& c){
	return (c.latitud > 0);
}

bool TieneCoordenadaIzquierda(Coordenada& c){
	return (c.longitud >0);
}

#endif
