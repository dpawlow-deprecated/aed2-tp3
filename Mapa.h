#ifndef MAPA_H
#define MAPA_H

#include <iostream>
#include "aed2.h"
#include "TiposJuego.h"

using namespace std;
using namespace aed2;

class Mapa {
public:
	Mapa(); //CrearMapa()
	Mapa(const Mapa&);
	Mapa& operator=(const Mapa&);
	~Mapa();
	Conj<Coordenada>& Coordenadas();
	void AgregarCoordenada (const Coordenada&);
	bool HayCamino(const Coordenada&, const Coordenada&);
	bool PosExistente(const Coordenada&);
	Nat Ancho() const { return _ancho; };
	Nat Alto() const { return _alto; };
	void Mostrar();
private:
	void calcular();
	Conj<Coordenada> CoordenadasConectadasA(Coordenada&);
	Conj<Coordenada> _coordenadas;
	Conj< Conj<Coordenada> > conectadasA;
	Nat _ancho;
	Nat _alto;
	bool** _relacionCoordenadas;
	Nat calcularPosicion(const Coordenada&);
};

#endif
