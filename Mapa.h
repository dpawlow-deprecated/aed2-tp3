#ifndef MAPA_H
#define MAPA_H

#include "Modulos-CPP/aed2/TiposBasicos.h"
#include "Modulos-CPP/aed2/Conj.h"
#include <iostream>
#include "TiposJuego.h"
#include "Coordenada.cpp"

using namespace std;
using namespace aed2;

class Mapa {
public:
	Mapa(); //CrearMapa()
	Mapa(const Mapa&);
	~Mapa();
	Conj<coordenada> Coordenadas();
	void AgregarCoordenada (const coordenada&);
	bool HayCamino(const coordenada&, const coordenada&);
	bool PosExistente(const coordenada&);
	Nat Ancho() const { return _ancho; };
	Nat Alto() const { return _alto; };
	void Mostrar();
private:
	Conj<coordenada> CoordenadasConectadasA(coordenada&) const;
	Conj<coordenada> _coordenadas;
	Nat _ancho;
	Nat _alto;
	bool** _relacionCoordenadas;
	Nat calcularPosicion(const coordenada&) const;
};

#endif
