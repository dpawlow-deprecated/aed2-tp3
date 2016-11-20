#include "Mapa.h"

Mapa::Mapa(){
	_coordenadas = Conj<Coordenada>();
	_ancho = 0;
	_alto = 0;
	_relacionCoordenadas = new bool*[0];
}

bool Mapa::HayCamino(const Coordenada& c1, const Coordenada& c2) {
	int pos1 = _ancho * c1.longitud + _alto * c1.latitud;
	int pos2 = _ancho * c2.longitud + _alto * c2.latitud;
	return _relacionCoordenadas[pos1][pos2];
}

Conj<Coordenada> Mapa::Coordenadas(){
	return _coordenadas;
}

bool Mapa::PosExistente(const Coordenada& c) {
	if (c.latitud > _alto && c.longitud > _ancho) {
		int pos = _ancho * c.longitud + _alto * c.latitud;
		return _relacionCoordenadas[pos][pos];
	}
	return false;
}


Conj<Coordenada> Mapa::CoordenadasConectadasA(const Coordenada&) const {
	Conj<Coordenada> coordenadas;
	return coordenadas;
}

void Mapa::AgregarCoordenada(const Coordenada& c1){
	/*if (Longitud(c) > ancho) { //Actualizo el ancho y alto del mapa
		ancho = c1.;
	}
	if (Latitud(c) > alto) {
		alto = Latitud(c);
	}*/

/*
	coordenadas.Agregar(c1); //Agrego la coordenada nueva a las coordenas del mapa

	relacionCoordenadas = new bool*[ancho*alto]; //Defino el espacio para las relaciones de las coordenadas

	Iterador iter = CrearIt(coordenadas)
	while HaySiguiente(iter) do
	coor ← Siguiente(iter)
	Avanzar(iter)
	conectadas ← iCoordenadasConectadas(coor, m)
	iterConectadas ← CrearIt(conectadas)
	while HaySiguiente(iterConectadas) do
	coor 2 ← Siguiente(iterConectadas)
	Avanzar(iterConectadas)
	pos1 ← m.ancho * Longitud(coor) + m.alto * Altitud(coor)
	pos2 ← m.ancho * Longitud(coor 2 ) + m.alto * Altitud(coor 2 )
	m.relacionCoordenadas[pos1][pos2] ← True
	m.relacionCoordenadas[pos2][pos1] ← True
	end while
	end while
*/
}
