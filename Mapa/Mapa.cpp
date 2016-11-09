#include "Mapa.h"

mapa::mapa(){
	Conj<Coordenada> c;
	bool** r = new bool*[0];
	coordenadas = c;
	ancho = 0;
	alto = 0;
	relacionCoordenadas = r;
}

Conj<Coordenada> mapa::Coordenadas(){
	return coordenadas;
}

void mapa::AgregarCoordenada(const Coordenada& c1){
if (Longitud(c) > ancho) { //Actualizo el ancho y alto del mapa
	ancho = Longitud(c);
}
if (Latitud(c) > alto) { 
	alto = Latitud(c);
}

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
}

int main(){
	return 0;
}