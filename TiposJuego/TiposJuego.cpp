#include "TiposJuego.h"
#include <iostream>

using namespace std;

int main(){
	//Algunos tests de coordenada 

	
	//Declaraciones de variables para test
	Nat i = 5;
	Nat j = 10;
	Coordenada c(i, j);
	Coordenada c1(j, i);
	Coordenada c2(5, 15);
	Coordenada c3(6, 12);
	Coordenada c5(0, 0);
	Coordenada c4 = CoordenadaArriba(c2);
	
	//Testeo de DistEuclidea
	cout << distanciaEuclidea(c, c1) << endl;
	cout << distanciaEuclidea(c2, c3) << endl;
	
	//Testeo de crear coordenadas abajo, arriba, izquierda, derecha
	cout << Latitud(c4) << "  " << Longitud(c4) << endl;
	c4 = CoordenadaAbajo(c2);
	cout << Latitud(c4) << "  " << Longitud(c4) << endl;
	c4 = CoordenadaIzquierda(c2);
	cout << Latitud(c4) << "  " << Longitud(c4) << endl;
	c4 = CoordenadaDerecha(c2);
	cout << Latitud(c4) << "  " << Longitud(c4) << endl;

	//Testeo de TieneCoordenadaIzquierda y TieneCoordenadaAbajo
	cout << TieneCoordenadaIzquierda(c2) << "   " << TieneCoordenadaIzquierda(c5) << endl; 
	cout << TieneCoordenadaAbajo(c2) << "   " << TieneCoordenadaAbajo(c5) << endl;
	return 0;

}