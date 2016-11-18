
#include <iostream>
#include "mini_test.h"

#include "DiccString.h"


//Chequea que el diccionario vacio no tenga claves
void test_claves_dicc_vacio2() {
	DiccString<int> d;
	ASSERT(!d.Definido("hola"));
	ASSERT(d.Claves().Longitud() == 0);
	d.Definir("hola", 1);
	ASSERT(d.Claves().Longitud() == 1);
	d.Definir("hoaeoueoau", 2);
	ASSERT(d.Claves().Longitud() == 2);
}


//Chequea el definir y definido
void test_definir_definido2() {
	DiccString<int> d;
	d.Definir("hola",42);
	ASSERT( d.Definido("hola") );
	ASSERT( !d.Definido("casona") );
 	ASSERT( !d.Definido("casa") );

	d.Definir("casona",13);
	ASSERT( d.Definido("hola") );
	ASSERT( d.Definido("casona") );
  	ASSERT( !d.Definido("casa") );

  	d.Definir("casa",6);
	ASSERT( d.Definido("hola") );
	ASSERT( d.Definido("casona") );
  	ASSERT( d.Definido("casa") );
}



//cheque el obtener
void test_obtener2() {
	DiccString<int> d;
	d.Definir("hola",42);
	d.Definir("casa",22);

	ASSERT( d.Significado("hola") == 42 );
	ASSERT( d.Significado("casa") == 22 );
	d.Definir("hola", 22);
	ASSERT(d.Significado("hola") == 22);
	d.Definir("hola", 24);
	ASSERT(d.Significado("hola") == 24);
	d.Definir("hola", 25);
	ASSERT(d.Significado("hola") == 25);
	d.Definir("h", 5);
	ASSERT(d.Significado("h") == 5);
	d.Definir("h", 6);
	ASSERT(d.Significado("h") == 6);
	d.Definir("h", 7);
	ASSERT(d.Significado("h") == 7);
	d.Definir("holas", 5);
	ASSERT(d.Significado("holas") == 5);
	d.Definir("holas", 6);
	ASSERT(d.Significado("holas") == 6);
}

//cheque el borrar
void test_borrar_uno2() {
	DiccString<int> d;
	d.Definir("casa", 1);
	d.Borrar("casa");
	ASSERT(d.Definido("casa") == false);
	ASSERT(d.Claves().Longitud() == 0);
}

void test_borrar2() {
	DiccString<int> d;
	d.Definir("hola",42);
	d.Definir("cas", 1);
	d.Definir("casa",22);
	d.Definir("casanova", 50);
 	d.Borrar("casa");

	ASSERT( d.Definido("cas") );
	ASSERT( d.Definido("hola") );
	ASSERT( d.Definido("casanova") );
	ASSERT(!d.Definido("casa") );
	
	d.Borrar("casanova");
	ASSERT( d.Definido("cas") );
	ASSERT( d.Definido("hola") );
	ASSERT(!d.Definido("casanova") );
	ASSERT(!d.Definido("casa") );
	
	d.Borrar("cas");
	ASSERT(!d.Definido("cas") );
	ASSERT( d.Definido("hola") );
	ASSERT(!d.Definido("casanova") );
	ASSERT(!d.Definido("casa") );

	d.Borrar("hola");
	ASSERT(!d.Definido("cas") );
	ASSERT(!d.Definido("hola") );
	ASSERT(!d.Definido("casanova") );
	ASSERT(!d.Definido("casa") );

	ASSERT(d.Claves().Longitud() == 0);
	
}

void test_copia_referencia2() {
	DiccString<int> d;
	d.Definir("hola",42);
	d.Definir("cas", 1);
	d.Definir("casa",22);
	d.Definir("casanova", 50);

	DiccString<int> d2(d);
	d.Borrar("casa");

	ASSERT(d.Claves().Longitud() == d2.Claves().Longitud()-1);
	ASSERT(d.Significado("hola") == d2.Significado("hola"));
	ASSERT(d.Significado("cas") == d2.Significado("cas"));
	ASSERT(d.Significado("casanova") == d2.Significado("casanova"));

	ASSERT(d.Definido("casa") == false);
	ASSERT(d2.Definido("casa") == true);
	ASSERT(d2.Significado("casa") == 22);
}


void test_todos_prefijos2() {
	DiccString<int> d;
	DiccString< DiccString<int> > d2;

	d.Definir("hola", 1);
	d2.Definir("uno", d);
	d.Definir("hola", 2);
	
	ASSERT(d2.Significado("uno").Significado("hola") == 1);
	ASSERT(d.Significado("hola") == 2);
	ASSERT(d2.Claves().Longitud() == 1);
	
	typename Lista<string>::const_Iterador it = d2.Claves().CrearIt();
	while(it.HaySiguiente() && it.Siguiente() != "uno"){
		it.Avanzar();
	}
	
	ASSERT(it.HaySiguiente() && it.Siguiente() == "uno");
	ASSERT(d2.Significado("uno").Significado("hola")     == 1);
	ASSERT(d2.Significado("uno").Definido("holas")   == false);
	ASSERT(d2.Significado("uno").Definido("holasa")  == false);
	ASSERT(d2.Definido("uno")  == true);
	ASSERT(d2.Definido("unodos")  == false);
	ASSERT(d2.Definido("unodostres") == false);

	
	d.Definir("holas", 2);
	d2.Definir("unodos", d);
	ASSERT(d2.Claves().Longitud() == 2);
	ASSERT(it.HaySiguiente() && it.Siguiente() == "uno");
	it = d2.Claves().CrearIt();
	while(it.HaySiguiente() && it.Siguiente() != "unodos"){
		it.Avanzar();
	}
	ASSERT(it.HaySiguiente() && it.Siguiente() == "unodos");
	ASSERT(d2.Significado("uno").Significado("hola")     == 1);
	ASSERT(d2.Significado("uno").Definido("holas")   == false);
	ASSERT(d2.Significado("uno").Definido("holasa")  == false);
	ASSERT(d2.Significado("unodos").Significado("hola")     == 2);
	ASSERT(d2.Significado("unodos").Significado("holas")    == 2);
	ASSERT(d2.Significado("unodos").Definido("holasa")  == false);
	ASSERT(d2.Definido("uno")  == true);
	ASSERT(d2.Definido("unodos")  == true);
	ASSERT(d2.Definido("unodostres") == false);

	d.Definir("holasa", 3);
	d2.Definir("unodostres", d);
	ASSERT(d2.Claves().Longitud() == 3);
	ASSERT(it.HaySiguiente() && it.Siguiente() == "unodos");
	it = d2.Claves().CrearIt();
	while(it.HaySiguiente() && it.Siguiente() != "uno"){
		it.Avanzar();
	}
	ASSERT(it.HaySiguiente() && it.Siguiente() == "uno");
	it = d2.Claves().CrearIt();
	while(it.HaySiguiente() && it.Siguiente() != "unodostres"){
		it.Avanzar();
	}
	ASSERT(it.HaySiguiente() && it.Siguiente() == "unodostres");
	ASSERT(d2.Significado("unodostres").Significado("hola")     == 2);
	ASSERT(d2.Significado("unodostres").Significado("holas")    == 2);
	ASSERT(d2.Significado("unodostres").Significado("holasa")   == 3);
	ASSERT(d.Definido("hola"));
	ASSERT(d.Definido("holasa"));
	ASSERT(d.Definido("holas"));
	ASSERT(d.Significado("hola") == 2);
	ASSERT(d.Significado("holas") == 2);
	ASSERT(d.Significado("holasa") == 3);
	ASSERT(d2.Definido("uno")  == true);
	ASSERT(d2.Definido("unodos")  == true);
	ASSERT(d2.Definido("unodostres") == true);
	
	d2.Borrar("uno");

	ASSERT(d2.Claves().Longitud() == 2);
	ASSERT(it.HaySiguiente() && it.Siguiente() == "unodostres");
	it = d2.Claves().CrearIt();
	while(it.HaySiguiente() && it.Siguiente() != "uno"){
		it.Avanzar();
	}
	ASSERT(!(it.HaySiguiente()));
	it = d2.Claves().CrearIt();
	while(it.HaySiguiente() && it.Siguiente() != "unodos"){
		it.Avanzar();
	}
	ASSERT(it.HaySiguiente() && it.Siguiente() == "unodos");
	ASSERT(d.Definido("hola"));
	ASSERT(d.Definido("holasa"));
	ASSERT(d.Definido("holas"));
	ASSERT(d.Significado("hola") == 2);
	ASSERT(d.Significado("holas") == 2);
	ASSERT(d.Significado("holasa") == 3);
	ASSERT(d2.Definido("uno") == false);
	ASSERT(d2.Definido("unodos") == true);
	ASSERT(d2.Definido("unodostres") == true);
	
	d2.Borrar("unodos");
	ASSERT(d2.Claves().Longitud() == 1);
	it = d2.Claves().CrearIt();
	while(it.HaySiguiente() && it.Siguiente() != "unodos"){
		it.Avanzar();
	}
	ASSERT(!(it.HaySiguiente()));
	it = d2.Claves().CrearIt();
	while(it.HaySiguiente() && it.Siguiente() != "uno"){
		it.Avanzar();
	}
	ASSERT(!(it.HaySiguiente()));
	it = d2.Claves().CrearIt();
	while(it.HaySiguiente() && it.Siguiente() != "unodostres"){
		it.Avanzar();
	}
	ASSERT(it.HaySiguiente() && it.Siguiente() == "unodostres");
	ASSERT(d.Definido("hola"));
	ASSERT(d.Definido("holasa"));
	ASSERT(d.Definido("holas"));
	ASSERT(d.Significado("hola") == 2);
	ASSERT(d.Significado("holas") == 2);
	ASSERT(d.Significado("holasa") == 3);
	ASSERT(d2.Definido("uno") == false);
	ASSERT(d2.Definido("unodos") == false);
	ASSERT(d2.Definido("unodostres") == true);
	
	d2.Borrar("unodostres");
	ASSERT(d2.Claves().Longitud() == 0);
	it = d2.Claves().CrearIt();
	while(it.HaySiguiente() && it.Siguiente() != "unodostres"){
		it.Avanzar();
	}
	ASSERT(!(it.HaySiguiente()));
	it = d2.Claves().CrearIt();
	while(it.HaySiguiente() && it.Siguiente() != "uno"){
		it.Avanzar();
	}
	ASSERT(!(it.HaySiguiente()));
	it = d2.Claves().CrearIt();
	while(it.HaySiguiente() && it.Siguiente() != "unodos"){
		it.Avanzar();
	}
	ASSERT(!(it.HaySiguiente()));
	ASSERT(d2.Definido("uno") == false);
	ASSERT(d2.Definido("unodos") == false);
	ASSERT(d2.Definido("unodostres") == false);
	ASSERT(d.Definido("hola"));
	ASSERT(d.Definido("holasa"));
	ASSERT(d.Definido("holas"));
	ASSERT(d.Significado("hola") == 2);
	ASSERT(d.Significado("holas") == 2);
	ASSERT(d.Significado("holasa") == 3);
	ASSERT(d2.Claves().Longitud() == 0);
	
}

void test_doble_definicion2() {
	DiccString<int> d;
	d.Definir("hola", 1);
	d.Definir("hola", 2);
	d.Definir("holas", 3);
	d.Definir("holas", 4);

	ASSERT(d.Significado("hola") == 2);
	ASSERT(d.Significado("holas") == 4);
}


void test_cardinal_claves2() {
	DiccString<int> d;
	d.Definir("hola", 10);

	DiccString<int> d2(d);
	d.Definir("chau", 10);

	ASSERT(d.Claves().Longitud() == 2);
	ASSERT(d2.Claves().Longitud() == 1);
}

void test_todos_prefijos_con_varias_hojas2() {
	DiccString<string> d;
	d.Definir("", "o");
	d.Definir("a", "o");
	d.Definir("ag", "o");
	d.Definir("aga", "o");
	d.Definir("agar", "o");
	d.Definir("agarr", "o");
	d.Definir("agarra", "o");
	d.Definir("agarram", "o");
	d.Definir("agarrame", "o");
	d.Definir("agarramel", "o");
	d.Definir("agarramela", "o");
	d.Definir("agarramelo", "o");
	d.Definir("agarramele", "o");
	d.Definir("agarramelu", "o");

	ASSERT(d.Claves().Longitud() == 14);
	d.Borrar("");
	ASSERT(d.Claves().Longitud() == 13);
	d.Borrar("a");
	ASSERT(d.Claves().Longitud() == 12);
	d.Borrar("ag");
	ASSERT(d.Claves().Longitud() == 11);
	d.Borrar("aga");
	ASSERT(d.Claves().Longitud() == 10);
	d.Borrar("agar");
	ASSERT(d.Claves().Longitud() == 9);
	d.Borrar("agarr");
	ASSERT(d.Claves().Longitud() == 8);
	d.Borrar("agarra");
	ASSERT(d.Claves().Longitud() == 7);
	d.Borrar("agarram");
	ASSERT(d.Claves().Longitud() == 6);
	d.Borrar("agarrame");
	ASSERT(d.Claves().Longitud() == 5);
	d.Borrar("agarramel");
	ASSERT(d.Claves().Longitud() == 4);
	d.Borrar("agarramela");
	ASSERT(d.Claves().Longitud() == 3);
	d.Borrar("agarramelo");
	ASSERT(d.Claves().Longitud() == 2);
	d.Borrar("agarramele");
	ASSERT(d.Claves().Longitud() == 1);
	d.Borrar("agarramelu");
	ASSERT(d.Claves().Longitud() == 0);
}
void test_claves_dicc_vacio() {
	DiccString<int> d;
	ASSERT(d.Claves().Longitud() == 0);
}


//Chequea el definir y definido
void test_definir_definido() {
	DiccString<int> d;
	d.Definir("hola",42);
	ASSERT( d.Definido("hola") );
	ASSERT( !d.Definido("casona") );
 	ASSERT( !d.Definido("casa") );

 	d.Definir("casona",13);
	ASSERT( d.Definido("hola") );
	ASSERT( d.Definido("casona") );
  	ASSERT( !d.Definido("casa") );

  	d.Definir("casa",6);
	ASSERT( d.Definido("hola") );
	ASSERT( d.Definido("casona") );
  	ASSERT( d.Definido("casa") );
  	
  	d.Borrar("casa");
  	ASSERT( d.Definido("hola") );
	ASSERT( d.Definido("casona") );
 	ASSERT( !d.Definido("casa") );
  	
  	d.Borrar("casona");
  	ASSERT( d.Definido("hola") );
	ASSERT( !d.Definido("casona") );
 	ASSERT( !d.Definido("casa") );
  	d.Borrar("hola");
  	ASSERT( !d.Definido("hola") );
	ASSERT( !d.Definido("casona") );
 	ASSERT( !d.Definido("casa") );
	
}



//cheque el obtener
void test_obtener() {
	DiccString<int> d;
	d.Definir("hola",42);
	d.Definir("casa",22);

	ASSERT( d.Significado("hola") == 42 );
	ASSERT( d.Significado("casa") == 22 );
	d.Definir("hola", 22);
	ASSERT(d.Significado("hola") == 22);

}

void test_joaco() {
	DiccString<int> d;
	d.Definir("hola",42);
	d.Definir("holaa",2);
	d.Definir("holasaasa",3);
	d.Definir("holasaasaa",4);
	d.Definir("hols", 32);
	d.Definir("ahhols", 33);
	d.Definir("h",44);
	ASSERT( d.Definido("hola") );
	ASSERT( d.Definido("holaa") );
	ASSERT( d.Definido("holasaasa") );
	ASSERT( d.Definido("holasaasaa") );
	ASSERT( d.Definido("hols") );
	ASSERT( d.Definido("ahhols") );
	ASSERT_EQ( d.Significado("hola"),42 );
	ASSERT_EQ( d.Significado("holaa"),2 );
	ASSERT_EQ( d.Significado("holasaasa"),3 );
	ASSERT_EQ( d.Significado("holasaasaa"),4 );
	ASSERT_EQ( d.Significado("hols"),32 );
	ASSERT_EQ( d.Significado("h"),44 );
	ASSERT_EQ( d.Significado("ahhols"),33 );

	//d.Definir("holasaasaa",5);
	//ASSERT( d.Definido("holasaasaa") );
	d.Borrar("holaa");
	//d.Borrar("h");
	//d.Borrar("holasaasaa");
	ASSERT( d.Definido("hola") );
	ASSERT( !d.Definido("holaa") );
	ASSERT( d.Definido("holasaasa") );
	ASSERT( d.Definido("holasaasaa") );
}


//cheque el borrar
void test_borrar() {
	//Completar este test para:
	//Verificar que al borrar una palabra, esta deja de estar definida en el diccionario
	//Chequear que si dos palabras comparten prefijos y una de ellas se borrar, la otra debe seguir estando definida
	//Analizar que el borrado funciona bien si el diccionario tiene definido una sola palabra y esta se borra.
	
	DiccString<int> d;
	d.Definir("hola",42);
	d.Definir("casa",22);
	d.Definir("casas",22);
	d.Definir("cascada",22);
 	
 	d.Borrar("casa");
	ASSERT( d.Definido("hola") );
	ASSERT(!d.Definido("casa") );
	ASSERT(!d.Definido("c"));
	ASSERT( d.Definido("casas") );
	ASSERT( d.Definido("cascada") );
	
	d.Borrar("hola");
	ASSERT(!d.Definido("hola"));
	
	d.Definir("casa", 22);
	d.Borrar("casas");
	
	ASSERT(d.Definido("casa"));
	ASSERT(d.Definido("cascada"));
	d.Borrar("cascada");
	ASSERT( !d.Definido("hola") );
	d.Borrar("casa");
	ASSERT(!d.Definido("casa") );
	ASSERT(!d.Definido("c"));
	ASSERT( !d.Definido("casas") );
	ASSERT( !d.Definido("cascada") );
	
	DiccString<int> d2;
	d2.Definir("h", 5);
	ASSERT(d2.Definido("h"));
	d2.Borrar("h");
	//ASSERT(!d2.Definido("h"));

}

void test_claves(){
	DiccString<int> d;
	d.Definir("hola",42);
	d.Definir("casa",22);
	d.Definir("h",4);
	d.Definir("c",2);
	d.Definir("gato",10);
	d.Definir("cascada",3);
	ASSERT(d.Claves().Longitud() == 6);
	
	typename Lista<string>::const_Iterador it = d.Claves().CrearIt();
	while(it.HaySiguiente() && it.Siguiente() != "hola"){
		it.Avanzar();
	}
	ASSERT(it.HaySiguiente() && it.Siguiente() == "hola");
	it = d.Claves().CrearIt();
	while(it.HaySiguiente() && it.Siguiente() != "h"){
		it.Avanzar();
	}
	ASSERT(it.HaySiguiente() && it.Siguiente() == "h");
	it = d.Claves().CrearIt();
	while(it.HaySiguiente() && it.Siguiente() != "gato"){
		it.Avanzar();
	}
	ASSERT(it.HaySiguiente() && it.Siguiente() == "gato");
	it = d.Claves().CrearIt();
	while(it.HaySiguiente() && it.Siguiente() != "casa"){
		it.Avanzar();
	}
	ASSERT(it.HaySiguiente() && it.Siguiente() == "casa");
	it = d.Claves().CrearIt();
	while(it.HaySiguiente() && it.Siguiente() != "c"){
		it.Avanzar();
	}
	ASSERT(it.HaySiguiente() && it.Siguiente() == "c");
	it = d.Claves().CrearIt();
	while(it.HaySiguiente() && it.Siguiente() != "cas"){
		it.Avanzar();
	}
	ASSERT(!(it.HaySiguiente()));
	
	d.Borrar("hola");
	ASSERT(d.Claves().Longitud() == 5);
	d.Borrar("casa");
	ASSERT(d.Claves().Longitud() == 4);
	d.Borrar("h");
	ASSERT(d.Claves().Longitud() == 3);
	d.Borrar("c");
	ASSERT(d.Claves().Longitud() == 2);
	d.Borrar("gato");
	ASSERT(d.Claves().Longitud() == 1);
	d.Borrar("cascada");
	ASSERT(d.Claves().Longitud() == 0);
	DiccString<int> d3;
	DiccString<int> d4(d3);
	ASSERT(d3.Claves().Longitud() == d4.Claves().Longitud())
	
}

void test_constructor_por_copia(){
	DiccString<int> d;
	d.Definir("hola",42);
	d.Definir("casa",22);
	d.Definir("h",4);
	d.Definir("c",2);
	d.Definir("gato",10);
	d.Definir("cascada",3);
	DiccString<int> d2(d);
	ASSERT(d2.Definido("hola"));
	ASSERT(d2.Definido("casa"));
	ASSERT(d2.Definido("cascada"));
	ASSERT(d2.Definido("gato"));
	ASSERT(d.Claves().Longitud() == d2.Claves().Longitud());
	d.Borrar("hola");
	ASSERT(!d.Definido("hola"));
	ASSERT(d2.Definido("hola"));
	d2.Borrar("gato");
	ASSERT(d.Definido("gato"));
	ASSERT(!d2.Definido("gato"));
	d.Borrar("gato");
	d2.Borrar("hola");
	d.Borrar("casa");
	d2.Borrar("casa");
	d.Borrar("h");
	d2.Borrar("h");
	d2.Definir("gcs", 6);
	d.Borrar("c");
	d2.Borrar("c");
	d.Definir("ff", 4);
	d.Borrar("cascada");
	d2.Borrar("cascada");
	ASSERT(d2.Claves().Longitud() == 1);
	ASSERT(d.Claves().Longitud() == 1);
	DiccString<int> d3(d2);
	ASSERT(d3.Definido("gcs"));
}

void test_crearIterado(){
	DiccString<int> d;
	d.Definir("hola", 8);
	d.Definir("casa", 9);

	DiccString<int>::const_Iterador it(d.CrearIt());

}

int main() {
	RUN_TEST(test_claves_dicc_vacio);
	RUN_TEST(test_claves_dicc_vacio2);
	RUN_TEST(test_definir_definido2);
	RUN_TEST(test_obtener2);
	RUN_TEST(test_borrar_uno2);
	RUN_TEST(test_borrar2);
	RUN_TEST(test_copia_referencia2);
	RUN_TEST(test_todos_prefijos2);
	RUN_TEST(test_doble_definicion2);
	RUN_TEST(test_cardinal_claves2);
	RUN_TEST(test_definir_definido);
	RUN_TEST(test_obtener);
	RUN_TEST(test_constructor_por_copia);
	RUN_TEST(test_todos_prefijos_con_varias_hojas2);
	RUN_TEST(test_joaco);
	RUN_TEST(test_borrar);
	RUN_TEST(test_claves);
	
	
	//NO FUNCIO CON DEFINICIONES VACIAS EL QUE LO QUIERA QUE LO PROGRAME


	//Realizar más test para chequear el funcionamiento del diccionario sobre trie.
	return 0;

}
