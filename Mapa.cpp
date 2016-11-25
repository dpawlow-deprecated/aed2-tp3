#include "Mapa.h"
#include "Cola.h"

Mapa::Mapa(){
	_coordenadas = Conj<Coordenada>();
	_ancho = 0;
	_alto = 0;
	_relacionCoordenadas = new bool*[0];
}

Mapa::Mapa(const Mapa& otro){
	Conj<Coordenada> c1(otro._coordenadas);
	_coordenadas = c1;
	Conj<Coordenada>::const_Iterador it = c1.CrearIt();
	while(it.HaySiguiente()){
		AgregarCoordenada(it.Siguiente());
		it.Avanzar();	
	}
}

Mapa::~Mapa() {
	for (int i = 0; i < _ancho*_alto; i++) {
		delete [] _relacionCoordenadas[i];
	}
	delete [] _relacionCoordenadas;
}

bool Mapa::HayCamino(const Coordenada& c1, const Coordenada& c2) {
	int pos1 = _ancho * c1.latitud + c1.longitud;
	int pos2 = _ancho * c2.latitud + c2.longitud;
	return _relacionCoordenadas[pos1][pos2];
}

Conj<Coordenada> Mapa::Coordenadas(){
	return _coordenadas;
}

bool Mapa::PosExistente(const Coordenada& c) {
	if (c.latitud < _alto && c.longitud < _ancho) {
		int pos = _ancho * c.longitud + _alto * c.latitud;
		return _relacionCoordenadas[pos][pos];
	}
	return false;
}


Conj<Coordenada> Mapa::CoordenadasConectadasA(Coordenada& c1) const {
	Conj<Coordenada> visitadas;
	Cola<Coordenada> aVisitar;
	aVisitar.Encolar(c1);
	Conj<Coordenada> coordenadas;
	coordenadas.Agregar(c1);

	while (aVisitar.EsVacia() == false) {
		Coordenada coor = aVisitar.Proximo();
		aVisitar.Desencolar();

		visitadas.Agregar(coor);

		if (coor.latitud > 0) {
			Coordenada coorAbajo = CoordenadaAbajo(coor);
			if (!visitadas.Pertenece(coorAbajo) && _coordenadas.Pertenece(coorAbajo)) {
				coordenadas.Agregar(coorAbajo);
				aVisitar.Encolar(coorAbajo);
			}
		}

		if (coor.longitud > 0) {
			Coordenada coorIzq = CoordenadaIzquierda(coor);
			if (!visitadas.Pertenece(coorIzq) && _coordenadas.Pertenece(coorIzq)) {
				coordenadas.Agregar(coorIzq);
				aVisitar.Encolar(coorIzq);
			}
		}

		Coordenada coorDer = CoordenadaDerecha(coor);
		if (!visitadas.Pertenece(coorDer) && _coordenadas.Pertenece(coorDer)) {
			coordenadas.Agregar(coorDer);
			aVisitar.Encolar(coorDer);
		}

		Coordenada coorArriba = CoordenadaDerecha(coor);
		if (!visitadas.Pertenece(coorArriba) && _coordenadas.Pertenece(coorArriba)) {
			coordenadas.Agregar(coorArriba);
			aVisitar.Encolar(coorArriba);
		}
	}
	return coordenadas;
}

void Mapa::AgregarCoordenada(const Coordenada& c){
	for (int i = 0; i < _ancho*_alto; i++) {
		delete [] _relacionCoordenadas[i];
	}
	delete [] _relacionCoordenadas;


	if ((c.longitud+1) > _ancho) { //Actualizo el ancho y alto del mapa
		_ancho = c.longitud+1; // este uno es porque hay que tener en cuenta la posicion 0
	}
	if ((c.latitud+1) > _alto) {
		_alto = c.latitud+1; // este uno es porque hay que tener en cuenta la posicion 0
	}

	_coordenadas.Agregar(c);

	_relacionCoordenadas = new bool*[_ancho*_alto];
	for (int i = 0; i < _ancho*_alto; i++) {
		_relacionCoordenadas[i] = new bool[_ancho*_alto];
		for (int j = 0; j < _ancho*_alto; j++) {
			_relacionCoordenadas[i][j] = false;
		}
	}

	Conj<Coordenada>::Iterador iter = _coordenadas.CrearIt();
	while (iter.HaySiguiente()) {
		Coordenada coor = iter.Siguiente();
		iter.Avanzar();

		Conj<Coordenada> conectadas = CoordenadasConectadasA(coor);
		Conj<Coordenada>::Iterador iterConectadas = conectadas.CrearIt();
		while (iterConectadas.HaySiguiente()) {
			Coordenada coor2 = iterConectadas.Siguiente();
			iterConectadas.Avanzar();
			int pos1 = _ancho * coor.latitud + coor.longitud;
			int pos2 = _ancho * coor2.latitud + coor2.longitud;
			_relacionCoordenadas[pos1][pos2] = true;
			_relacionCoordenadas[pos2][pos1] = true;
		}
	}
}
