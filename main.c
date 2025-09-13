#include <stdio.h>
#include <string.h>
#include "src/tp1.h"
#define ERROR -1
#define ARCHIVO_PRUEBA_INEXISTENTE "ejemplos/asdkasjhfskladjhfksdfhksdf.csv"
#define ARCHIVO_PRUEBA_VACIO "ejemplos/vacio.csv"
#define ARCHIVO_PRUEBA_NORMAL "ejemplos/normal.csv"
#define ARCHIVO_PRUEBA_NORMAL_2 "ejemplos/normal_2.csv"
#define ARCHIVO_PRUEBA_INVALIDO "ejemplos/sin_coma.csv"
#define ARCHIVO_STAT_INVALIDO "ejemplos/stat_invalida.csv"
#define ARCHIVO_TIPO_INVALIDO "ejemplos/tipo_invalido.csv"
#define ARCHIVO_LINEAS_VACIAS "ejemplos/lineas_vacias.csv"
#define ARCHIVO_PARA_GUARDAR "ejemplos/guardado.csv"
#define ARCHIVO_REPETIDOS "ejemplos/repetidos.csv"
#define ARCHIVO_UNIDOS "ejemplos/normal_unidos.csv"
#define ARCHIVO_UNO_SOLO "ejemplos/uno_solo.csv"
#define ARCHIVO_DESORDENADO "ejemplos/desordenado.csv"

/*
./tp1 pokedex.csv buscar nombre pikachu: Busca un pokemon con el nombre pikachu y si lo encuentra muestra la información por pantalla.
./tp1 pokedex.csv buscar id 25: Busca un pokemon con el id 25 y si lo encuentra muestra la información por pantalla.
./tp1 pokedex.csv union pokedex2.csv resultado.csv: Carga la pokedex y la pokedex2 y guarda en resultado la union de ambas.
./tp1 pokedex.csv interseccion pokedex2.csv resultado.csv: Carga la pokedex y la pokedex2 y guarda en resultado la inserseccion de ambas.
./tp1 pokedex.csv diferencia pokedex2.csv resultado.csv: Carga la pokedex y la pokedex2 y guarda en resultado la diferencia de ambas.
./tp1 pokedex.csv mostrar nombre: Muestra todos los pokemon por orden alfabetico
./tp1 pokedex.csv mostrar id: Muestra todos los pokemon por orden numerico
*/



bool mostrar_pokemon(struct pokemon *pokemon, void* extra)
{
	if (pokemon == NULL)
		return false;
	printf("%s\n", pokemon->nombre);
	return true;
}



// Devuelve true si el texto es igual a comando
bool es_comando(char* texto, char* comando) {
	if (strcmp(texto,comando) == 0)
		return true;
	return false;
}

bool comando_es_valido(char* comando)
{
	if(es_comando(comando, "buscar"))
		return true;
	return false;
}

//Recibe la cantidad de argumentos en el comando, y el comando especificado.
//Devuelve true si la cantidad es la que debería ser. Si no, devuelve false.
bool cantidad_args_es_correcta(int argc, char *comando)
{
	if(es_comando(comando, "buscar"))
		if (argc == 5)
			return true;
	return false;
}

bool archivo_no_existe(char *nombre)
{
	if (tp1_leer_archivo(nombre) == NULL)
		return true;
	return false;
}
// !!!!!!!!! SIGUIENTE TAREA: MODULARIZAR, HACER TODOS LOS RETURN FALSES Y CREAR FUNCION BOOL DE CHEQUEO GENERAL 

void procesar_comando(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Se debe especificar un archivo.\n");
		return;
	}
	if (argc < 3) {
		printf("Se debe especificar un comando.\n");
		return;
	}
	if (archivo_no_existe(argv[1])) {
		printf("El archivo indicado no existe.\n");
		return;
	}
	if(!comando_es_valido(argv[2])) {
		printf("El comando indicado no existe.\n");
		return;
	}
	if (!cantidad_args_es_correcta(argc, argv[2])) {
		printf("La cantidad de argumentos es incorrecta.\n");
		return;
	}
	printf("La cantidad de argumentos es correcta! Pero no cree el comando! jeje\n");
}

int main(int argc, char *argv[])
{
	procesar_comando(argc, argv);
	return 0;
}
