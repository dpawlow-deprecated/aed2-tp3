#ifndef COORDENADA_H_
#define COORDENADA_H_

#include "TiposJuego.h"
#include <cmath>

using namespace std;

class coordenada{
	public:
		coordenada(const coordenada&);
		coordenada(Nat, Nat);
		coordenada coordenadaAbajo(const coordenada);
		coordenada coordenadaIzquierda(const coordenada);
		coordenada coordenadaDerecha(const coordenada);
		coordenada coordenadaArriba(const coordenada);
		Nat distanciaEuclidea(const coordenada& c1);
		Nat Latitud() const;
		Nat Longitud()const;
		bool TieneCoordenadaAbajo();
		bool TieneCoordenadaIzquierda();
	private:
		Nat latitud;
		Nat longitud;
};

bool operator == (const coordenada& c1, const coordenada& c2){
 return c1.Latitud() == c2.Latitud() and c1.Longitud() == c2.Longitud();
}

bool operator != (const coordenada& c1, const coordenada& c2){
 return not (c1 == c2);
}

#endif