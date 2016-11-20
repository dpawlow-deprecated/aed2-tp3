#ifndef MAPA_H
#define MAPA_H

#include "Modulos-CPP/aed2/TiposBasicos.h"
#include "Modulos-CPP/aed2/Conj.h"
#include <iostream>
#include "TiposJuego.h"

using namespace std;
using namespace aed2;

class Mapa {
public:
	Mapa(); //CrearMapa()
	Conj<Coordenada> Coordenadas();
	void AgregarCoordenada (const Coordenada&);
	bool HayCamino(const Coordenada&, const Coordenada&);
	bool PosExistente(const Coordenada&);
	Nat Ancho() { return ancho; };
	Nat Alto() { return alto; };
private:
	Conj<Coordenada> coordenadas;
	Nat ancho;
	Nat alto;
	bool** relacionCoordenadas;
};

#endif
