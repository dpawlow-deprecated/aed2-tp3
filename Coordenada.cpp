#include "Coordenada.h"

coordenada::coordenada(const coordenada& otra){
	latitud = otra.latitud;
	longitud = otra.longitud;
};

coordenada::coordenada(Nat lat, Nat lon):latitud(lat), longitud(lon){};

coordenada coordenada::coordenadaAbajo(const coordenada otra){
	coordenada c(otra.latitud -1, otra.longitud);
	return c;
}

coordenada coordenada::coordenadaIzquierda(const coordenada otra){
	coordenada c(otra.latitud, otra.longitud -1);
	return c;
}

coordenada coordenada::coordenadaDerecha(const coordenada otra){
	coordenada c(otra.latitud, otra.longitud +1);
	return c;
}

coordenada coordenada::coordenadaArriba(const coordenada otra){
	coordenada c(otra.latitud +1, otra.longitud);
	return c;
}

Nat coordenada::distanciaEuclidea(const coordenada& c1){
	return sqrt((c1.latitud - latitud) * (c1.latitud - latitud) + (c1.longitud - longitud) * (c1.longitud - longitud));
}

Nat coordenada::Latitud()const{
	return latitud;
}

Nat coordenada::Longitud()const{
	return longitud;
}

bool coordenada::TieneCoordenadaAbajo(){
	return (latitud >0);
}

bool coordenada::TieneCoordenadaIzquierda(){
	return (longitud >0);
}