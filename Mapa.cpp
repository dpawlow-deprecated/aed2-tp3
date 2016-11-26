#include "Mapa.h"
#include "Cola.h"

Mapa::Mapa(): _ancho(0), _alto(0), _relacionCoordenadas(NULL){
	_coordenadas = Conj<coordenada>();
}

Mapa::Mapa(const Mapa& otro): _ancho(0), _alto(0), _relacionCoordenadas(NULL) {
	Conj<coordenada> c1(otro._coordenadas);
	_coordenadas = c1;
	Conj<coordenada>::const_Iterador it = c1.CrearIt();
	while (it.HaySiguiente()) {
		AgregarCoordenada(it.Siguiente());
		it.Avanzar();
	}
}

Mapa::~Mapa() {
	for (int i = 0; i < _ancho*_alto; i++) {
		delete [] _relacionCoordenadas[i];
	}
	if (_relacionCoordenadas != NULL) {
		delete [] _relacionCoordenadas;
	}
}

bool Mapa::HayCamino(const coordenada& c1, const coordenada& c2) {
	int pos1 = calcularPosicion(c1);
	int pos2 = calcularPosicion(c2);
	return _relacionCoordenadas[pos1][pos2];
}

Conj<coordenada> Mapa::Coordenadas(){
	return _coordenadas;
}

bool Mapa::PosExistente(const coordenada& c) {
	if (c.Latitud() < _alto && c.Longitud() < _ancho) {
		int pos = calcularPosicion(c);
		return _relacionCoordenadas[pos][pos];
	}
	return false;
}


Conj<coordenada> Mapa::CoordenadasConectadasA(coordenada& c1) const {
	Conj<coordenada> visitadas;
	Cola<coordenada> aVisitar;
	aVisitar.Encolar(c1);
	Conj<coordenada> coordenadas;
	coordenadas.Agregar(c1);

	while (aVisitar.EsVacia() == false) {
		coordenada coor = aVisitar.Proximo();
		aVisitar.Desencolar();

		visitadas.Agregar(coor);

		if (coor.Latitud() > 0) {
			coordenada coorAbajo = coor.coordenadaAbajo(coor);
			if (!visitadas.Pertenece(coorAbajo) && _coordenadas.Pertenece(coorAbajo)) {
				coordenadas.Agregar(coorAbajo);
				aVisitar.Encolar(coorAbajo);
			}
		}

		if (coor.Longitud() > 0) {
			coordenada coorIzq = coor.coordenadaIzquierda(coor);
			if (!visitadas.Pertenece(coorIzq) && _coordenadas.Pertenece(coorIzq)) {
				coordenadas.Agregar(coorIzq);
				aVisitar.Encolar(coorIzq);
			}
		}

		coordenada coorDer = coor.coordenadaDerecha(coor);
		if (!visitadas.Pertenece(coorDer) && _coordenadas.Pertenece(coorDer)) {
			coordenadas.Agregar(coorDer);
			aVisitar.Encolar(coorDer);
		}

		coordenada coorArriba = coor.coordenadaDerecha(coor);
		if (!visitadas.Pertenece(coorArriba) && _coordenadas.Pertenece(coorArriba)) {
			coordenadas.Agregar(coorArriba);
			aVisitar.Encolar(coorArriba);
		}
	}
	return coordenadas;
}

void Mapa::AgregarCoordenada(const coordenada& c){
	for (int i = 0; i < _ancho*_alto; i++) {
		delete [] _relacionCoordenadas[i];
	}
	if (_relacionCoordenadas != NULL) {
		delete [] _relacionCoordenadas;
	}


	if ((c.Longitud()+1) > _ancho) { //Actualizo el ancho y alto del mapa
		_ancho = c.Longitud()+1; // este uno es porque hay que tener en cuenta la posicion 0
	}
	if ((c.Latitud()+1) > _alto) {
		_alto = c.Latitud()+1; // este uno es porque hay que tener en cuenta la posicion 0
	}

	_coordenadas.Agregar(c);

	int tamanioArreglo = (_ancho+1)*(_alto+1);
	_relacionCoordenadas = new bool*[tamanioArreglo];
	for (int i = 0; i < tamanioArreglo; i++) {
		_relacionCoordenadas[i] = new bool[tamanioArreglo];
		for (int j = 0; j < tamanioArreglo; j++) {
			_relacionCoordenadas[i][j] = false;
		}
	}

	Conj<coordenada>::Iterador iter = _coordenadas.CrearIt();
	while (iter.HaySiguiente()) {
		coordenada coor = iter.Siguiente();
		iter.Avanzar();

		Conj<coordenada> conectadas = CoordenadasConectadasA(coor);
		Conj<coordenada>::Iterador iterConectadas = conectadas.CrearIt();
		while (iterConectadas.HaySiguiente()) {
			coordenada coor2 = iterConectadas.Siguiente();
			iterConectadas.Avanzar();
			int pos1 = calcularPosicion(coor);
			int pos2 = calcularPosicion(coor2);
			_relacionCoordenadas[pos1][pos2] = true;
			_relacionCoordenadas[pos2][pos1] = true;
		}
	}
}

Nat Mapa::calcularPosicion(const coordenada& c) const{
	return _ancho * c.Latitud() + c.Longitud();
}
