// Compilar usando:
//	g++ -o tests tests.cpp Driver.cpp juego.cpp ColaPrioridad.hpp Mapa.cpp DiccString.hpp IteradorMagico.hpp
//  g++ -o tests tests.cpp juego.cpp ColaPrioridad.hpp Mapa.cpp DiccString.hpp IteradorMagico.hpp
//	valgrind --leak-check=full ./tests


#include "mini_test.h"
#include "aed2.h"
#include "Driver.cpp"
#include "Mapa.cpp"
#include "Juego.cpp"
#include "aed2.h"
#include "aed2/TiposBasicos.h"
#include "TiposJuego.h"
#include "Coordenada.cpp"


using namespace aed2;


void agregar_coodenadas_a_mapa() {
    Conj<Coordenada> cc;
    cc.AgregarRapido(Coordenada(0,0));
    cc.AgregarRapido(Coordenada(0,1));
    cc.AgregarRapido(Coordenada(0,2));
    cc.AgregarRapido(Coordenada(1,2));
    cc.AgregarRapido(Coordenada(10,0));
    cc.AgregarRapido(Coordenada(1,4));
    Conj<Coordenada>::Iterador it = cc.CrearIt();
    Mapa m;
    while(it.HaySiguiente()){
        Coordenada c = it.Siguiente();
        m.AgregarCoordenada(c);
        it.Avanzar();
    }
    Driver d = Driver(cc);
    ASSERT( m.Coordenadas() == cc );
    ASSERT( d.mapa() == cc );
}

void ancho_largo_correcto() {
    Conj<Coordenada> cc;
    Mapa m;
    cc.AgregarRapido(Coordenada(0,0));
    cc.AgregarRapido(Coordenada(0,1));
    cc.AgregarRapido(Coordenada(0,2));
    cc.AgregarRapido(Coordenada(1,2));
    cc.AgregarRapido(Coordenada(10,5));
    cc.AgregarRapido(Coordenada(1,4));
    Conj<Coordenada>::Iterador it = cc.CrearIt();
    while(it.HaySiguiente()){
        Coordenada c = it.Siguiente();
        m.AgregarCoordenada(c);
        it.Avanzar();
    }

    ASSERT( m.Alto() == 11 );
    ASSERT( m.Ancho() == 6 );
}

void constructor_por_copia_mapa(){
    Conj<Coordenada> cc;
    cc.AgregarRapido(Coordenada(0,0));
    cc.AgregarRapido(Coordenada(0,1));
    cc.AgregarRapido(Coordenada(0,2));
    cc.AgregarRapido(Coordenada(1,2));
    cc.AgregarRapido(Coordenada(10,0));
    cc.AgregarRapido(Coordenada(1,4));
    Conj<Coordenada>::Iterador it = cc.CrearIt();
    Mapa m;
    while(it.HaySiguiente()){
        Coordenada c = it.Siguiente();
        m.AgregarCoordenada(c);
        it.Avanzar();
    }

    Mapa m2 = Mapa(m);
    ASSERT( m2.PosExistente(Coordenada(1,4)) == m.PosExistente(Coordenada(1,4)) );
    ASSERT( m2.PosExistente(Coordenada(11,0)) == m.PosExistente(Coordenada(11,0)) );
    ASSERT( m2.Alto() == m.Alto() );
    ASSERT( m2.Ancho() == m.Ancho() );
    ASSERT( m2.Coordenadas() == cc );
}

void test_agregar_pokemones(){
    Conj<Coordenada> cc;
    cc.AgregarRapido(Coordenada(0,0));
    cc.AgregarRapido(Coordenada(0,1));

    Driver d = Driver(cc);
    Pokemon p = "pikachu";
    d.agregarPokemon(p, Coordenada(0,0));
    d.agregarPokemon(p, Coordenada(0,1));
}

void test_hay_camino(){
    Conj<Coordenada> cc;
    Coordenada c1 = Coordenada(0,0);
    Coordenada c2 = Coordenada(0,1);
    Coordenada c3 = Coordenada(0,10);
    cc.AgregarRapido(c1);
    cc.AgregarRapido(c2);
    cc.AgregarRapido(c3);

    Driver d = Driver(cc);
    ASSERT(d.hayCamino(c1, c2));
    ASSERT(d.hayCamino(c2, c1));
    ASSERT(!d.hayCamino(c2, c3));
    ASSERT(!d.hayCamino(c1, c3));
    ASSERT(!d.hayCamino(c3, c1));
    ASSERT(!d.hayCamino(c3, c2));
}

void test_pos_existente(){
    Conj<Coordenada> cc;
    Coordenada c1 = Coordenada(0,0);
    Coordenada c2 = Coordenada(0,1);
    Coordenada c3 = Coordenada(0,10);
    cc.AgregarRapido(c1);
    cc.AgregarRapido(c2);
    cc.AgregarRapido(c3);

    Driver d = Driver(cc);
    ASSERT(d.posExistente(c1));
    ASSERT(d.posExistente(c2));
    ASSERT(d.posExistente(c3));
    ASSERT(!d.posExistente(Coordenada(100, 100)));
    ASSERT(!d.posExistente(Coordenada(2, 0)));
    ASSERT(!d.posExistente(Coordenada(0, 2)));
    ASSERT(!d.posExistente(Coordenada(1, 1)));
}

void test_agregar_jugadores(){
    Conj<Coordenada> cc;
    cc.AgregarRapido(Coordenada(0,0));
    cc.AgregarRapido(Coordenada(0,1));

    Driver d = Driver(cc);
    Jugador j = d.agregarJugador();
    Jugador j1 = d.agregarJugador();

    ASSERT(j != j1);
    ASSERT(j < j1);
    ASSERT(j == 0);
    ASSERT(j1 == 1);
}


void test_jugadores_agregados(){
    Conj<Coordenada> cc;
    cc.AgregarRapido(Coordenada(0,0));
    cc.AgregarRapido(Coordenada(0,1));

    Driver d = Driver(cc);
    Jugador j = d.agregarJugador();
    Jugador j1 = d.agregarJugador();

    Conj<Jugador > jugadores;
    jugadores.AgregarRapido(j);
    jugadores.AgregarRapido(j1);

    ASSERT(jugadores == d.jugadores());
}


void test_conectarse(){
    Conj<Coordenada> cc;
    Coordenada c1 = Coordenada(0,0);
    Coordenada c2 = Coordenada(6,1);
    Coordenada c3 = Coordenada(5,3);
    Coordenada c4 = Coordenada(10,9);
    Coordenada c5 = Coordenada(6,41);
    Coordenada c6 = Coordenada(2,4);

    cc.AgregarRapido(c1);
    cc.AgregarRapido(c2);
    cc.AgregarRapido(c3);
    cc.AgregarRapido(c4);
    cc.AgregarRapido(c5);
    cc.AgregarRapido(c6);

    Driver d = Driver(cc);
    Pokemon p = "pikachu";
    d.agregarPokemon(p, c1);

    Jugador j1 = d.agregarJugador();
    Jugador j2 = d.agregarJugador();
    Jugador j3 = d.agregarJugador();
    Jugador j4 = d.agregarJugador();
    Jugador j5 = d.agregarJugador();
    Jugador j6 = d.agregarJugador();
    d.conectarse(j1, c1);
    d.conectarse(j2, c1);
    d.conectarse(j3, c3);
    d.conectarse(j4, c4);
    d.conectarse(j5, c5);
    d.conectarse(j6, c6);
    ASSERT(d.posicion(j1) == c1);
    ASSERT(d.posicion(j2) == c1);
    ASSERT(d.posicion(j1) == c1);
    ASSERT(d.posicion(j3) == c3);
    ASSERT(d.estaConectado(j3));
    ASSERT(d.posicion(j4) == c4);
    ASSERT(d.posicion(j5) == c5);
    ASSERT(d.posicion(j6) == c6);
}

void test_desconectarse(){
    Conj<Coordenada> cc;
    Coordenada c1 = Coordenada(0,0);
    Coordenada c2 = Coordenada(0,1);
    Coordenada c3 = Coordenada(0,10);
    cc.AgregarRapido(c1);
    cc.AgregarRapido(c2);
    cc.AgregarRapido(c3);

    Driver d = Driver(cc);

    Jugador j = d.agregarJugador();
    Jugador j2 = d.agregarJugador();
    d.conectarse(j, c1);
    d.conectarse(j2, c1);

    d.desconectarse(j2);
    d.desconectarse(j);
}

void test_esta_conectado(){
    Conj<Coordenada> cc;
    Coordenada c1 = Coordenada(0,0);
    Coordenada c2 = Coordenada(0,1);
    Coordenada c3 = Coordenada(0,10);
    cc.AgregarRapido(c1);
    cc.AgregarRapido(c2);
    cc.AgregarRapido(c3);

    Driver d = Driver(cc);

    Jugador j = d.agregarJugador();
    Jugador j2 = d.agregarJugador();
    Jugador j3 = d.agregarJugador();

    Conj<Jugador > jugadores;
    jugadores.AgregarRapido(j);
    jugadores.AgregarRapido(j2);
    jugadores.AgregarRapido(j3);

    d.conectarse(j, c1);
    d.conectarse(j2, c1);
    d.conectarse(j3, c1);

    ASSERT(d.estaConectado(j));
    ASSERT(d.estaConectado(j2));
    ASSERT(d.estaConectado(j3));
    d.desconectarse(j);
    ASSERT(!d.estaConectado(j));
    ASSERT(d.estaConectado(j2));
    ASSERT(d.estaConectado(j3));
    d.desconectarse(j2);
    ASSERT(!d.estaConectado(j));
    ASSERT(!d.estaConectado(j2));
    ASSERT(d.estaConectado(j3));
    d.desconectarse(j3);
    ASSERT(!d.estaConectado(j));
    ASSERT(!d.estaConectado(j2));
    ASSERT(!d.estaConectado(j3));
    ASSERT(d.jugadores() == jugadores);
}

void test_sanciones(){
    Conj<Coordenada> cc;
    Coordenada c1 = Coordenada(0,0);
    Coordenada c2 = Coordenada(0,1);
    Coordenada c3 = Coordenada(0,10);
    cc.AgregarRapido(c1);
    cc.AgregarRapido(c2);
    cc.AgregarRapido(c3);

    Driver d = Driver(cc);

    Jugador j = d.agregarJugador();
    d.conectarse(j, c1);

    ASSERT(d.sanciones(j) == 0);
}

void test_posicion_jugador(){
    Conj<Coordenada> cc;
    Coordenada c1 = Coordenada(0,0);
    Coordenada c2 = Coordenada(0,1);
    Coordenada c3 = Coordenada(0,10);
    cc.AgregarRapido(c1);
    cc.AgregarRapido(c2);
    cc.AgregarRapido(c3);

    Driver d = Driver(cc);

    Jugador j = d.agregarJugador();
    d.conectarse(j, c1);
    ASSERT(d.posicion(j) == c1);
}


void test_pokemon_en_pos(){
    Conj<Coordenada> cc;
    Coordenada c1 = Coordenada(0,0);
    Coordenada c2 = Coordenada(0,1);
    Coordenada c3 = Coordenada(0,10);
    cc.AgregarRapido(c1);
    cc.AgregarRapido(c2);
    cc.AgregarRapido(c3);

    Driver d = Driver(cc);
    Pokemon p = "pikachu";
    d.agregarPokemon(p,c1);

    ASSERT(d.pokemonEnPos(c1) == p);
}

void test_puedo_agregar_pokemon(){
    Conj<Coordenada> cc;
    Coordenada c1 = Coordenada(0,0);
    Coordenada c2 = Coordenada(5,5);
    Coordenada c3 = Coordenada(0,5);
    Coordenada c4 = Coordenada(1,3);
    Coordenada c5 = Coordenada(4,3);
    Coordenada c6 = Coordenada(4,2);
    cc.AgregarRapido(c1);
    cc.AgregarRapido(c2);
    cc.AgregarRapido(c3);
    cc.AgregarRapido(c4);
    cc.AgregarRapido(c5);
    cc.AgregarRapido(c6);
    Driver d = Driver(cc);

    Pokemon p = "pikachu";
    d.agregarPokemon(p,c1);
    ASSERT(!d.puedoAgregarPokemon(c1));
    ASSERT(d.puedoAgregarPokemon(c2));
    ASSERT(!d.puedoAgregarPokemon(c3));
    ASSERT(!d.puedoAgregarPokemon(c4));
    ASSERT(!d.puedoAgregarPokemon(c5));
    ASSERT(!d.puedoAgregarPokemon(c6));
}

void test_hay_pokemon_cercano(){

    Conj<Coordenada> cc;
    Coordenada c1 = Coordenada(10,3);
    Coordenada c2 = Coordenada(10,0);
    Coordenada c3 = Coordenada(5,3);
    Coordenada c4 = Coordenada(4,3);
    Coordenada c5 = Coordenada(1,4);
    Coordenada c6 = Coordenada(1,3);
    Coordenada c7 = Coordenada(1,2);
    Coordenada c8 = Coordenada(1,0);
    Coordenada c9 = Coordenada(0,5);
    Coordenada c10 = Coordenada(0,4);
    Coordenada c11 = Coordenada(0,2);
    Coordenada c12 = Coordenada(0,1);
    Coordenada c13 = Coordenada(0,0);

    cc.AgregarRapido(c1);
    cc.AgregarRapido(c2);
    cc.AgregarRapido(c3);
    cc.AgregarRapido(c4);
    cc.AgregarRapido(c5);
    cc.AgregarRapido(c6);
    cc.AgregarRapido(c7);
    cc.AgregarRapido(c8);
    cc.AgregarRapido(c9);
    cc.AgregarRapido(c10);
    cc.AgregarRapido(c11);
    cc.AgregarRapido(c12);
    cc.AgregarRapido(c13);

    Driver d = Driver(cc);

    ASSERT(!d.hayPokemonCercano(c1));
    ASSERT(!d.hayPokemonCercano(c2));
    ASSERT(!d.hayPokemonCercano(c3));
    ASSERT(!d.hayPokemonCercano(c4));
    ASSERT(!d.hayPokemonCercano(c5));
    ASSERT(!d.hayPokemonCercano(c6));
    ASSERT(!d.hayPokemonCercano(c7));
    ASSERT(!d.hayPokemonCercano(c8));
    ASSERT(!d.hayPokemonCercano(c9));
    ASSERT(!d.hayPokemonCercano(c10));
    ASSERT(!d.hayPokemonCercano(c11));
    ASSERT(!d.hayPokemonCercano(c12));
    ASSERT(!d.hayPokemonCercano(c13));

    Pokemon p1 = "P1";
    Pokemon p2 = "P2";
    Pokemon p3 = "P3";

    d.agregarPokemon(p1,c13);


    ASSERT(!d.hayPokemonCercano(c1));
    ASSERT(!d.hayPokemonCercano(c2));
    ASSERT(!d.hayPokemonCercano(c3));
    ASSERT(!d.hayPokemonCercano(c4));
    ASSERT(!d.hayPokemonCercano(c5));
    ASSERT(d.hayPokemonCercano(c6));
    ASSERT(d.hayPokemonCercano(c7));
    ASSERT(d.hayPokemonCercano(c8));
    ASSERT(!d.hayPokemonCercano(c9));
    ASSERT(d.hayPokemonCercano(c10));
    ASSERT(d.hayPokemonCercano(c11));
    ASSERT(d.hayPokemonCercano(c12));
    ASSERT(d.hayPokemonCercano(c13));


    d.agregarPokemon(p2,c2);

    ASSERT(d.hayPokemonCercano(c1));
    ASSERT(d.hayPokemonCercano(c2));
    ASSERT(!d.hayPokemonCercano(c3));
    ASSERT(!d.hayPokemonCercano(c4));
    ASSERT(!d.hayPokemonCercano(c5));
    ASSERT(d.hayPokemonCercano(c6));
    ASSERT(d.hayPokemonCercano(c7));
    ASSERT(d.hayPokemonCercano(c8));
    ASSERT(!d.hayPokemonCercano(c9));
    ASSERT(d.hayPokemonCercano(c10));
    ASSERT(d.hayPokemonCercano(c11));
    ASSERT(d.hayPokemonCercano(c12));
    ASSERT(d.hayPokemonCercano(c13));

    d.agregarPokemon(p3,c4);


    ASSERT(d.hayPokemonCercano(c1));
    ASSERT(d.hayPokemonCercano(c2));
    ASSERT(d.hayPokemonCercano(c3));
    ASSERT(d.hayPokemonCercano(c4));
    ASSERT(d.hayPokemonCercano(c5));
    ASSERT(d.hayPokemonCercano(c6));
    ASSERT(d.hayPokemonCercano(c7));
    ASSERT(d.hayPokemonCercano(c8));
    ASSERT(!d.hayPokemonCercano(c9));
    ASSERT(d.hayPokemonCercano(c10));
    ASSERT(d.hayPokemonCercano(c11));
    ASSERT(d.hayPokemonCercano(c12));
    ASSERT(d.hayPokemonCercano(c13));
}

void test_pos_pokemon_cercano(){
    Conj<Coordenada> cc;
    Coordenada c1 = Coordenada(0,0);
    Coordenada c2 = Coordenada(0,5);
    Coordenada c3 = Coordenada(0,4);
    Coordenada c4 = Coordenada(1,5);
    cc.AgregarRapido(c1);
    cc.AgregarRapido(c2);
    cc.AgregarRapido(c3);
    cc.AgregarRapido(c4);

    Driver d = Driver(cc);
    Pokemon p = "pikachu";
    d.agregarPokemon(p,c1);

    ASSERT(d.posPokemonCercano(c2) == c1);
    ASSERT(d.posPokemonCercano(c3) == c1);


}

void test_cantMismaEspecie(){
    Conj<Coordenada> cc;
    Coordenada c1 = Coordenada(0,0);
    Coordenada c2 = Coordenada(0,1);
    Coordenada c3 = Coordenada(0,10);
    Coordenada c4 = Coordenada(0,15);
    Coordenada c5 = Coordenada(5,10);
    Coordenada c6 = Coordenada(5,15);
    Coordenada c7 = Coordenada(5,20);
    Coordenada c8 = Coordenada(5,30);
    cc.AgregarRapido(c1);
    cc.AgregarRapido(c2);
    cc.AgregarRapido(c3);
    cc.AgregarRapido(c4);
    cc.AgregarRapido(c5);
    cc.AgregarRapido(c6);
    cc.AgregarRapido(c7);
    cc.AgregarRapido(c8);

    Driver d = Driver(cc);
    Pokemon p1 = "pikachu";
    d.agregarPokemon(p1,c1);
    Pokemon p2 = "pikachu";
    d.agregarPokemon(p2,c3);
    Pokemon p3 = "pikachu";
    d.agregarPokemon(p3,c7);
    Pokemon p4 = "pikachu";
    d.agregarPokemon(p4,c4);
    Pokemon p5 = "cacho";
    d.agregarPokemon(p5,c8);
    ASSERT(d.cantMismaEspecie(p1)==4);
    ASSERT(d.cantMismaEspecie(p5)==1);
}

void test_pos_pokemons(){
    Conj<Coordenada> cc;
    Coordenada c1 = Coordenada(0,0);
    Coordenada c2 = Coordenada(0,5);
    Coordenada c3 = Coordenada(0,4);
    Coordenada c4 = Coordenada(1,5);
    cc.AgregarRapido(c1);
    cc.AgregarRapido(c2);
    cc.AgregarRapido(c3);
    cc.AgregarRapido(c4);

    Driver d = Driver(cc);
    Pokemon p1 = "pikachu";
    d.agregarPokemon(p1,c1);
    d.agregarPokemon(p1,c4);
    Conj<Coordenada> cp;
    cp.AgregarRapido(c1);
    cp.AgregarRapido(c4);

    ASSERT(d.posConPokemons() == cp);
    cp.AgregarRapido(c3);
    ASSERT(not (d.posConPokemons() == cp));
}

void test_pTotales(){
    Conj<Coordenada> cc;
    Coordenada c1 = Coordenada(0,0);
    Coordenada c2 = Coordenada(0,1);
    Coordenada c3 = Coordenada(0,10);
    Coordenada c4 = Coordenada(0,15);
    Coordenada c5 = Coordenada(5,10);
    Coordenada c6 = Coordenada(5,15);
    Coordenada c7 = Coordenada(5,20);
    Coordenada c8 = Coordenada(5,30);
    cc.AgregarRapido(c1);
    cc.AgregarRapido(c2);
    cc.AgregarRapido(c3);
    cc.AgregarRapido(c4);
    cc.AgregarRapido(c5);
    cc.AgregarRapido(c6);
    cc.AgregarRapido(c7);
    cc.AgregarRapido(c8);

    Driver d = Driver(cc);
    Pokemon p1 = "pikachu";
    d.agregarPokemon(p1,c1);
    Pokemon p2 = "pikachu";
    d.agregarPokemon(p2,c3);
    Pokemon p3 = "pikachu";
    d.agregarPokemon(p3,c7);
    Pokemon p4 = "pikachu";
    d.agregarPokemon(p4,c4);
    Pokemon p5 = "cacho";
    d.agregarPokemon(p5,c8);
    ASSERT(d.cantPokemonsTotales()==5);
}

void test_indiceRareza(){
    Conj<Coordenada> cc;
    Coordenada c1 = Coordenada(0,0);
    Coordenada c2 = Coordenada(0,1);
    Coordenada c3 = Coordenada(0,10);
    Coordenada c4 = Coordenada(0,15);
    Coordenada c5 = Coordenada(5,10);
    Coordenada c6 = Coordenada(5,15);
    Coordenada c7 = Coordenada(5,20);
    Coordenada c8 = Coordenada(5,30);
    cc.AgregarRapido(c1);
    cc.AgregarRapido(c2);
    cc.AgregarRapido(c3);
    cc.AgregarRapido(c4);
    cc.AgregarRapido(c5);
    cc.AgregarRapido(c6);
    cc.AgregarRapido(c7);
    cc.AgregarRapido(c8);

    Driver d = Driver(cc);
    Pokemon p1 = "pikachu";
    d.agregarPokemon(p1,c1);
    Pokemon p2 = "pikachu";
    d.agregarPokemon(p2,c3);
    Pokemon p3 = "pikachu";
    d.agregarPokemon(p3,c7);
    Pokemon p4 = "pikachu";
    d.agregarPokemon(p4,c4);
    Pokemon p5 = "cacho";
    d.agregarPokemon(p5,c8);
    ASSERT(d.indiceRareza(p1)==20);
    ASSERT(d.indiceRareza(p5)==80);

    Jugador j0 = d.agregarJugador();
    Jugador j1 = d.agregarJugador();
    Jugador j2 = d.agregarJugador();
    d.conectarse(j0, c1);
    d.conectarse(j1, c1);

    d.conectarse(j2, c5);

    d.moverse(j2, c5);
    d.moverse(j2, c5);
    d.moverse(j2, c5);
    d.moverse(j2, c5);
    d.moverse(j2, c5);
    d.moverse(j2, c5);
    d.moverse(j2, c5);
    d.moverse(j2, c5);
    d.moverse(j2, c5);
    d.moverse(j2, c5);
    Dicc<Pokemon, Nat> dic;
    dic.Definir(p1, 1);
    ASSERT(d.pokemons(j0) == dic);

    ASSERT(d.indiceRareza(p1)==20);
    ASSERT(d.indiceRareza(p5)==80);

}

void test_poke_catedra(){
    Conj<Coordenada> cc;
    Coordenada c1 = Coordenada(120,2);
    Coordenada c2 = Coordenada(12,2);
    Coordenada c3 = Coordenada(12,1);
    Coordenada c4 = Coordenada(12,0);
    Coordenada c6 = Coordenada(2,0);
    Coordenada c7 = Coordenada(1,0);
    Coordenada c8 = Coordenada(0,0);
    cc.AgregarRapido(c1);
    cc.AgregarRapido(c2);
    cc.AgregarRapido(c3);
    cc.AgregarRapido(c4);
    cc.AgregarRapido(c6);
    cc.AgregarRapido(c7);
    cc.AgregarRapido(c8);

    Driver d = Driver(cc);
    d.agregarPokemon("Squirtle", Coordenada(0,0));
    d.agregarPokemon("Ratatta", Coordenada(12,0));
    d.agregarPokemon("Ratatta", Coordenada(120,2));

    Jugador j0 = d.agregarJugador();
    Jugador j1 = d.agregarJugador();
    Jugador j2 = d.agregarJugador();
    d.conectarse(j0, Coordenada(0,0)); // sqrt
    d.conectarse(j1, Coordenada(12,0)); // rtt
    d.conectarse(j2, Coordenada(120,2)); //rtt

    d.moverse(j1, Coordenada(12,1));
    d.moverse(j1, Coordenada(12,0));
    d.moverse(j1, Coordenada(12,1));
    d.moverse(j1, Coordenada(12,0));
    d.moverse(j1, Coordenada(12,1));
    d.moverse(j1, Coordenada(12,0));
    d.moverse(j1, Coordenada(12,1));
    d.moverse(j1, Coordenada(12,0));
    d.moverse(j1, Coordenada(12,1));
    d.moverse(j1, Coordenada(12,0));
    d.moverse(j1, Coordenada(12,1));

    d.moverse(j2, Coordenada(12,0));
    d.moverse(j2, Coordenada(120,0));
    d.moverse(j2, Coordenada(12,0));
    d.moverse(j2, Coordenada(120,0));
    d.moverse(j2, Coordenada(12,0));
    std::cout << std::endl << d.indiceRareza("Squirtle") << std::endl;
    ASSERT(d.indiceRareza("Squirtle") == 50);
    ASSERT(d.indiceRareza("Ratatta") == 50);

}

///////////////////////// TEST COLA DE PRIORIDAD ///////////////////////////

void test_colaPrior_encolar() {
	ColaPrioridad <int> c;
	c.encolar(4);
	c.encolar(2);
	c.encolar(14);
	c.encolar(24);
	c.encolar(526);
	ASSERT(c.proximo()==2);
	c.desencolar();
	ASSERT(c.proximo()==4);
	c.desencolar();
	ASSERT(c.proximo()==14);
	c.desencolar();
	ASSERT(c.proximo()==24);
	c.desencolar();
	ASSERT(c.proximo()==526);
	c.desencolar();
}

void test_colaPrior_proximo() {
	ColaPrioridad <int> c;
	c.encolar(-4);
	ASSERT(c.proximo()==-4);
	c.encolar(-2);
	ASSERT(c.proximo()==-4);
	c.encolar(-14);
	ASSERT(c.proximo()==-14);
	c.encolar(-24);
	ASSERT(c.proximo()==-24);
	c.encolar(-526);
	ASSERT(c.proximo()==-526);
	c.encolar(-28);
	ASSERT(c.proximo()==-526);
	c.encolar(13);
	ASSERT(c.proximo()==-526);
}

void test_colaPrior_estaVacio() {
	ColaPrioridad <int> c;
	c.encolar(-4);
	c.encolar(-442);
	c.encolar(424);
	c.encolar(454);
	c.encolar(-123);
	c.encolar(98);
	c.encolar(0);
	c.desencolar();
	c.desencolar();
	c.desencolar();
	c.desencolar();
	c.desencolar();
	c.desencolar();
	c.desencolar();
	ASSERT(c.preguntarVacia());
	c.encolar(0);
	ASSERT(!c.preguntarVacia());
}

void test_colaPrior_borrar() {
	ColaPrioridad <int> c;
	c.encolar(424);
	ColaPrioridad<int>::Iterador a(c.encolar(4513));
	ColaPrioridad<int>::Iterador b(c.encolar(-41));
	ColaPrioridad<int>::Iterador c2(c.encolar(-141));
	c.encolar(20);
	ASSERT(c.proximo()==-141);
	c2.Borrar();
	ASSERT(c.proximo()==-41);
	b.Borrar();
	ASSERT(c.proximo()==20);
	a.Borrar();
	ASSERT(c.proximo()==20);
	c.desencolar();
	ASSERT(c.proximo()==424);
	c.desencolar();
	ASSERT(c.preguntarVacia());
	c.encolar(0);
}

void test_itcolaPrior_actual() {
	ColaPrioridad <int> c;
	ColaPrioridad<int>::Iterador a (c.encolar(4513));
	ColaPrioridad<int>::Iterador b (c.encolar(-41));
	ColaPrioridad<int>::Iterador c2(c.encolar(-141));
	ASSERT(a .Siguiente()==4513);
	ASSERT(b .Siguiente()==-41);
	ASSERT(c2.Siguiente()==-141);
}

void test_itcolaPrior_eliminarIt() {
	ColaPrioridad <int> c;
	typename ColaPrioridad <int>::Iterador a(c.encolar(4513));
	typename ColaPrioridad <int>::Iterador b(c.encolar(-41));
	c.encolar(10);
	typename ColaPrioridad <int>::Iterador c2(c.encolar(-141));
	c2.Borrar();
	ASSERT(c.proximo()==-41);
	b.Borrar();
	ASSERT(c.proximo()==10);
	a.Borrar();
	c.desencolar();
	ASSERT(c.preguntarVacia());
	c.encolar(0);
}

/////////////////////////////////////////////////////////////////////////

void test_entrenadoresPosibles(){
    Conj<Coordenada> cc;
    Coordenada c1 = Coordenada(0,0);
    Coordenada c2 = Coordenada(0,1);
    Coordenada c3 = Coordenada(0,10);
    Coordenada c4 = Coordenada(0,4);
    Coordenada c5 = Coordenada(5,10);
    Coordenada c6 = Coordenada(5,12);
    Coordenada c7 = Coordenada(5,20);
    Coordenada c8 = Coordenada(5,30);
    Coordenada c9 = Coordenada(5,22);

    cc.AgregarRapido(c1);
    cc.AgregarRapido(c2);
    cc.AgregarRapido(c3);
    cc.AgregarRapido(c4);
    cc.AgregarRapido(c5);
    cc.AgregarRapido(c6);
    cc.AgregarRapido(c7);
    cc.AgregarRapido(c8);
    cc.AgregarRapido(c9);

    Driver d = Driver(cc);
    Pokemon p1 = "pikachu";
    d.agregarPokemon(p1,c1);
    Pokemon p2 = "pikachu";
    d.agregarPokemon(p2,c3);
    Pokemon p3 = "pikachu";
    d.agregarPokemon(p3,c4);
    Pokemon p4 = "pikachu";
    d.agregarPokemon(p4,c7);
    Pokemon p5 = "cacho";
    d.agregarPokemon(p5,c8);

    Jugador j1 = d.agregarJugador();
    Jugador j2 = d.agregarJugador();
    Jugador j3 = d.agregarJugador();
    Jugador j4 = d.agregarJugador();
    Jugador j5 = d.agregarJugador();
    Jugador j6 = d.agregarJugador();
    Jugador j7 = d.agregarJugador();

    d.conectarse(j1, c2);
    d.conectarse(j2, c2);
    d.conectarse(j3, c5);
    d.conectarse(j4, c5);
    d.conectarse(j5, c5);
    d.conectarse(j6, c5);
    d.conectarse(j7, c9);

}

void test_cantMovimientosParaCaptura(){
    Conj<Coordenada> cc;
    Coordenada c1 = Coordenada(120,2);
    Coordenada c2 = Coordenada(12,2);
    Coordenada c3 = Coordenada(12,1);
    Coordenada c4 = Coordenada(12,0);
    Coordenada c5 = Coordenada(3,0);
    Coordenada c6 = Coordenada(2,0);
    Coordenada c7 = Coordenada(1,0);
    Coordenada c8 = Coordenada(0,0);
    cc.AgregarRapido(c1);
    cc.AgregarRapido(c2);
    cc.AgregarRapido(c3);
    cc.AgregarRapido(c4);
    cc.AgregarRapido(c5);
    cc.AgregarRapido(c6);
    cc.AgregarRapido(c7);
    cc.AgregarRapido(c8);

    Driver d = Driver(cc);
    Pokemon p1 = "Squirtle";
    d.agregarPokemon(p1,c8);
    ASSERT(d.cantMovimientosParaCaptura(c8) == 0);
    d.agregarPokemon(p1,c1);

    /**
     * Hay 2 pokemones, 1 en 0,0 y otro en 120,2
     */
    ASSERT(d.cantMovimientosParaCaptura(c1) == 0);
    Jugador j0 = d.agregarJugador();
    Jugador j1 = d.agregarJugador();
    Jugador j2 = d.agregarJugador();

    /**
    * Jugador 0 en 12,0
    * Jugador 2 en 120,2
    * Jugador 1 en 0, 0
    */
    d.conectarse(j0,c4);
    d.conectarse(j1,c8);
    d.conectarse(j2,c1);
    d.moverse(j0,c3);
    /**
     * Jugador 0 se mueve a 12, 1, movimiento para captura del poke 120,2 y 0,0
     * Ya que hubo movimiento externo.
     */
    ASSERT(d.cantMovimientosParaCaptura(c8) == 1);
    ASSERT(d.cantMovimientosParaCaptura(c1) == 1);
    /**
     * Jugador 0 se mueve a 12, 2, movimiento para captura del poke 120,2 y 0,0
     * Ya que hubo movimiento externo.
     */
    d.moverse(j0,c2);
    ASSERT(d.cantMovimientosParaCaptura(c8) == 2);
    ASSERT(d.cantMovimientosParaCaptura(c1) == 2);
    /**
     * Jugador 0 se mueve a 12, 1, movimiento para captura del poke 120,2 y 0,0
     * Ya que hubo movimiento externo.
     */
    d.moverse(j0,c3);
    ASSERT(d.cantMovimientosParaCaptura(c8) == 3);
    ASSERT(d.cantMovimientosParaCaptura(c1) == 3);
    /**
     * Jugador 0 se mueve a 0,0 pero es movimiento invalido, con lo cual queda en 12, 1
     * Ya que hubo movimiento externo.
     */
    d.moverse(j0,c8);
    ASSERT(d.cantMovimientosParaCaptura(c8) == 3);
    ASSERT(d.cantMovimientosParaCaptura(c1) == 3);
    /**
     * J1, que estaba en 0,0 se mueve a 3,0, tendria que haber camino
     * y como es un movimiento interno, no cuenta en 0,0  = 3 movs y cuenta en 120,2 = 4 movs
     */


    d.moverse(j1,c5);//ACA EXPLOTA

    /**
     * J1, que estaba en 3,0 se mueve a 1,0, tendria que haber camino
     * y como es un movimiento interno, no cuenta en 0,0  = 3 movs y cuenta en 120,2 = 5 movs
     */
    d.moverse(j1,c7); //FALTA ESTE CASO: cuando el jugador entra al rango de un pokemon sin estar esperando

    ASSERT(d.cantMovimientosParaCaptura(c8) == 3);
    ASSERT(d.cantMovimientosParaCaptura(c1) == 5);
}

void test_moverse_con_camino_sin_pokes(){
    Conj<Coordenada> cc;
    Coordenada c1 = Coordenada(7,7);
    Coordenada c2 = Coordenada(7,6);
    Coordenada c3 = Coordenada(5,5);
    Coordenada c4 = Coordenada(5,6);
    Coordenada c5 = Coordenada(6,6);
    Coordenada c6 = Coordenada(6,5);
    cc.AgregarRapido(c1);
    cc.AgregarRapido(c2);
    cc.AgregarRapido(c3);
    cc.AgregarRapido(c4);
    cc.AgregarRapido(c5);
    cc.AgregarRapido(c6);
    Driver d = Driver(cc);
    Jugador jugador = d.agregarJugador();
    d.conectarse(jugador, c3);
	d.moverse(jugador, c1);
	ASSERT(d.posicion(jugador) == c1);
	ASSERT(d.sanciones(jugador) == 0);
}

/*void test_moverse_caso1(){
	Mapa m;
	m.AgregarCoordenada(Coordenada(7,7));
	m.AgregarCoordenada(Coordenada(7,6));
	m.AgregarCoordenada(Coordenada(5,5));
	Juego j (m);
	j.AgregarJugador();
	j.Conectarse(0, Coordenada(7,7));
  j.Moverse(0, Coordenada(5,5));
	ASSERT(j.Sanciones(0) == 1);
	ASSERT(j.Posicion(0).latitud == 5);
	ASSERT(j.Posicion(0).longitud == 5);
}

void test_moverse_caso2(){
	Mapa m;
	m.AgregarCoordenada(Coordenada(7,7));
	m.AgregarCoordenada(Coordenada(7,6));
	m.AgregarCoordenada(Coordenada(5,5));
	Juego j (m);
	j.AgregarJugador();
	j.AgregarPokemon("r", Coordenada(5,5));
	j.AgregarPokemon("a", Coordenada(7,7));
	j.Conectarse(0, Coordenada(5,5));
    j.Moverse(0, Coordenada(7,7));
	ASSERT(j.Sanciones(0) == 1);
	ASSERT(j.Posicion(0).latitud == 7);
	ASSERT(j.Posicion(0).longitud == 7);
}

void test_moverse_caso3(){
	Mapa m;
	m.AgregarCoordenada(Coordenada(7,7));
	m.AgregarCoordenada(Coordenada(7,6));
	m.AgregarCoordenada(Coordenada(5,5));
	Juego j (m);
	j.AgregarJugador();
	j.AgregarPokemon("r",Coordenada(5,5));
	j.Conectarse(0,Coordenada(5,5));
	j.Moverse(0,Coordenada(7,7));
	ASSERT(j.Sanciones(0) == 1);
	ASSERT(j.Posicion(0).latitud == 7);
	ASSERT(j.Posicion(0).longitud == 7);
}

void test_moverse_caso4(){
	Mapa m;
	m.AgregarCoordenada(Coordenada(7,7));
	m.AgregarCoordenada(Coordenada(7,6));
	m.AgregarCoordenada(Coordenada(5,5));
	Juego j (m);
	j.AgregarJugador();
	j.AgregarPokemon("r", Coordenada(7,7));
	j.Conectarse(0, Coordenada(5,5));
	j.Moverse(0, Coordenada(7,7));
	ASSERT(j.Sanciones(0) == 1);
	ASSERT(j.Posicion(0).latitud == 7);
	ASSERT(j.Posicion(0).longitud == 7);

	// Alternativamente:
	// j.Conectarse(0, {7,6});
	// j.Moverse(0, {7,7});
}*/

void test_coordenada_en_el_limite(){
	Mapa m;
	m.AgregarCoordenada(Coordenada(7,7));
	m.AgregarCoordenada(Coordenada(6,6));
	Juego j (m);
	j.AgregarPokemon("pepe", Coordenada(6,6));

  //TODO: revisar esta linea
	//ASSERT(j.MapaDeJuego().verParticion(Coordenada(7,7)) != j.MapaDeJuego().verParticion(Coordenada(6,6)));
	ASSERT(j.HayPokemonCercano(Coordenada(7,7)));
	ASSERT(j.PosPokemonCercano(Coordenada(7,7)).latitud == 6);
	ASSERT(j.PosPokemonCercano(Coordenada(7,7)).longitud == 6);
}

/*void test_moverse_expulsar(){
	Mapa m;
	m.AgregarCoordenada(Coordenada(7,7));
	m.AgregarCoordenada(Coordenada(7,6));
	m.AgregarCoordenada(Coordenada(5,5));
	Juego j (m);
	j.AgregarJugador();
	j.AgregarPokemon("r", Coordenada(5,5));
	j.Conectarse(0, Coordenada(5,5));
	Nat i = 2;
	while (i > 0){
		j.Moverse(0, Coordenada(7,7));
		j.Moverse(0, Coordenada(5,5));
		i--;
	}
	j.Moverse(0, Coordenada(7,7));
  //TODO: ver como arreglamos esto
	//ASSERT(j.Expulsados().HaySiguiente());
	//ASSERT(j.Expulsados().Siguiente().Id_ == 0);
}*/

void test_expulsados(){
    Conj<Coordenada> cc;
    Coordenada c1 = Coordenada(7,7);
    Coordenada c2 = Coordenada(7,6);
    Coordenada c3 = Coordenada(5,5);
    Coordenada c4 = Coordenada(5,6);
    Coordenada c5 = Coordenada(6,6);
    Coordenada c6 = Coordenada(6,5);
    Coordenada c7 = Coordenada(120,2);
    Coordenada c8 = Coordenada(0,0);
    cc.AgregarRapido(c1);
    cc.AgregarRapido(c2);
    cc.AgregarRapido(c3);
    cc.AgregarRapido(c4);
    cc.AgregarRapido(c5);
    cc.AgregarRapido(c6);
    cc.AgregarRapido(c7);
    cc.AgregarRapido(c8);
    Driver d = Driver(cc);
    Jugador j = d.agregarJugador();
    ASSERT(d.expulsados() == Conj<Jugador>());
    d.conectarse(j, c7);
    d.moverse(j, c8);
    d.moverse(j, c8);
    d.moverse(j, c8);
    d.moverse(j, c8);
    d.moverse(j, c8);
    ASSERT(d.sanciones(j) == 5);
}

void test_mover_jugador_asigna_correcta_coordenada(){
    Conj<Coordenada> cc;
    Coordenada c1 = Coordenada(1,4);
    Coordenada c3 = Coordenada(1,2);
    Coordenada c4 = Coordenada(10,0);
    Coordenada c2 = Coordenada(0,1);
    Coordenada c5 = Coordenada(0,2);
    Coordenada c6 = Coordenada(0,0);

    cc.AgregarRapido(c1);
    cc.AgregarRapido(c2);
    cc.AgregarRapido(c3);
    cc.AgregarRapido(c4);
    cc.AgregarRapido(c5);
    cc.AgregarRapido(c6);

    Driver d = Driver(cc);
    Jugador j0 = d.agregarJugador();
    Jugador j1 = d.agregarJugador();
    Jugador j2 = d.agregarJugador();
    Jugador j3 = d.agregarJugador();

    d.conectarse(j0, c6);
    d.conectarse(j1, c6);
    d.conectarse(j2, c5);
    d.conectarse(j3, c2);
    d.moverse(j0, c6);

    ASSERT(d.posicion(j0) == c6);
    ASSERT(d.posicion(j1) == c6);
    ASSERT(d.posicion(j2) == c5);
    ASSERT(d.posicion(j3) == c2);
    d.moverse(j1, c3);

    ASSERT(d.posicion(j0) == c6);
    ASSERT(d.posicion(j1) == c3);
    ASSERT(d.posicion(j2) == c5);
    ASSERT(d.posicion(j3) == c2);
    d.moverse(j2, c4);

    ASSERT(d.posicion(j0) == c6);
    ASSERT(d.posicion(j1) == c3);
    ASSERT(d.posicion(j2) == c5);
    ASSERT(d.posicion(j3) == c2);
}

//void test_cantidad_de_pokemons_totales_usando_mover(){
    //Dicc<Pokemon, Nat> lospoke0;
    //lospoke0.Definir(p, 1);
    //ASSERT(d.pokemons(j0) == lospoke0);
//}



void test_atrapar_pokemon_test_simple(){
    Conj<Coordenada> cc;
    Coordenada c1 = Coordenada(11,0);
    Coordenada c2 = Coordenada(10,0);
    Coordenada c3 = Coordenada(3,0);
    Coordenada c4 = Coordenada(2,0);
    Coordenada c5 = Coordenada(1,0);
    Coordenada c6 = Coordenada(0,0);

    cc.AgregarRapido(c1);
    cc.AgregarRapido(c2);
    cc.AgregarRapido(c3);
    cc.AgregarRapido(c4);
    cc.AgregarRapido(c5);
    cc.AgregarRapido(c6);

    Driver d = Driver(cc);
    Pokemon p = "sqrt";
    d.agregarPokemon(p, c6);

    Jugador j0 = d.agregarJugador();
    Jugador j1 = d.agregarJugador();
    d.conectarse(j0, c4);
    d.conectarse(j1, c1);
    d.moverse(j1, c2);
    d.moverse(j1, c1);
    d.moverse(j1, c2);
    d.moverse(j1, c1);
    d.moverse(j1, c2);
    d.moverse(j1, c1);
    d.moverse(j1, c2);
    d.moverse(j1, c1);
    d.moverse(j1, c2);
    d.moverse(j1, c1);
    Dicc<Pokemon, Nat> lospoke0;
    Dicc<Pokemon, Nat> lospoke1;
    lospoke0.Definir(p, 1);
    d.pokemons(j1);
    d.pokemons(j0);
    ASSERT(d.pokemons(j0) == lospoke0);

}

void test_valgrind()
{
    Conj< Coordenada > cc;
    cc.Agregar(Coordenada(0,0));
    cc.Agregar(Coordenada(1,0));
    cc.Agregar(Coordenada(2,0));

    cc.Agregar(Coordenada(12,0));
    cc.Agregar(Coordenada(12,1));
    cc.Agregar(Coordenada(12,2));

    cc.Agregar(Coordenada(120,2));
    cc.Agregar(Coordenada(120,3));

    Driver d(cc);

    d.agregarPokemon("Squirtle", Coordenada(0,0));
    d.agregarPokemon("Rattata", Coordenada(12,0));
    d.agregarPokemon("Squirtle", Coordenada(120,2));

    ASSERT(d.cantMismaEspecie("Squirtle") == 2);
    ASSERT(d.cantMismaEspecie("Rattata") == 1);

    Nat j1 = d.agregarJugador();
    Nat j2 = d.agregarJugador();
    Nat j3 = d.agregarJugador();

    d.conectarse(j2, Coordenada(0,0));
    d.conectarse(j1, Coordenada(12,0));
    d.conectarse(j3, Coordenada(120,2));

    d.moverse(j2, Coordenada(12,0));
    d.moverse(j2, Coordenada(120,2));
    d.moverse(j1, Coordenada(12,1));

    for(int i = 0; i < 5; i++ )
    {
        d.moverse(j3, Coordenada(120,3));
        d.moverse(j3, Coordenada(120,2));
    }

}

int main(int argc, char **argv)
{
/**
 * Test dudosos
 */
    /*RUN_TEST(test_cantMovimientosParaCaptura);
    RUN_TEST(test_hay_pokemon_cercano);
    RUN_TEST(test_moverse_caso1);
    RUN_TEST(test_moverse_caso2);
    RUN_TEST(test_moverse_caso3);
    RUN_TEST(test_moverse_expulsar);*/

    /**
     * Tests pasan ok 0 errores de valgrind
     */


    RUN_TEST(test_valgrind);
    RUN_TEST(test_atrapar_pokemon_test_simple);
    RUN_TEST(agregar_coodenadas_a_mapa);
    RUN_TEST(ancho_largo_correcto);
    RUN_TEST(constructor_por_copia_mapa);
    RUN_TEST(test_hay_camino);
    RUN_TEST(test_pos_existente);
    RUN_TEST(test_agregar_pokemones);
    RUN_TEST(test_agregar_jugadores);
    RUN_TEST(test_jugadores_agregados);
    RUN_TEST(test_conectarse);
    RUN_TEST(test_desconectarse);
    RUN_TEST(test_esta_conectado);
    RUN_TEST(test_sanciones);
    RUN_TEST(test_posicion_jugador);
    RUN_TEST(test_colaPrior_encolar);
    RUN_TEST(test_colaPrior_proximo);
    RUN_TEST(test_colaPrior_estaVacio);
    RUN_TEST(test_colaPrior_borrar);
    RUN_TEST(test_itcolaPrior_actual);
    RUN_TEST(test_itcolaPrior_eliminarIt);
    RUN_TEST(test_pokemon_en_pos);
    RUN_TEST(test_puedo_agregar_pokemon);
    RUN_TEST(test_pos_pokemon_cercano);
    RUN_TEST(test_cantMismaEspecie);
    RUN_TEST(test_pTotales);
    RUN_TEST(test_indiceRareza);
    RUN_TEST(test_pos_pokemons);
    RUN_TEST(test_entrenadoresPosibles);
    RUN_TEST(test_moverse_con_camino_sin_pokes);



    ////*******************************************************************************************//
    ////Las funciones de arriba segun valgrind no pieden memoria. Las de abajo no las testee porque//
    ////todavia no estan terminadas ni validadas. (sin embargo, aparentemente tampoco pierden).    //
    ////*******************************************************************************************//


    RUN_TEST(test_coordenada_en_el_limite);
    RUN_TEST(test_expulsados);
    RUN_TEST(test_mover_jugador_asigna_correcta_coordenada);
    RUN_TEST(test_poke_catedra);

  return 0;
}
