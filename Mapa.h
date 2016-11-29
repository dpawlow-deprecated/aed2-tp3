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
	Conj<Coordenada> Coordenadas();
	void AgregarCoordenada (const Coordenada&);
	bool HayCamino(const Coordenada&, const Coordenada&);
	bool PosExistente(const Coordenada&);
	Nat Ancho() const { return _ancho; };
	Nat Alto() const { return _alto; };
	void Mostrar();
private:
	Conj<Coordenada> CoordenadasConectadasA(Coordenada&) const;
	Conj<Coordenada> _coordenadas;
	Nat _ancho;
	Nat _alto;
	bool** _relacionCoordenadas;
	Nat calcularPosicion(const Coordenada&) const;
};

#endif
