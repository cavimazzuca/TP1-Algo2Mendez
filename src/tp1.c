#include "tp1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define LETRAS_LEIDAS_POR_ITERACION 10
#define TEXTO_ELEC "ELEC"
#define TEXTO_FUEG "FUEG"
#define TEXTO_PLAN "PLAN"
#define TEXTO_AGUA "AGUA"
#define TEXTO_NORM "NORM"
#define TEXTO_FANT "FANT"
#define TEXTO_PSI "PSI"
#define TEXTO_LUCH "LUCH"
#define ERROR -1

struct tp1 {
	struct pokemon *pokemones;
	size_t cantidad;
};



/*
 * Retorna la posición de 'linea' en donde encuentra el primer '\n'.
 * 'linea' debe ser un string. 
 */
char *salto_encontrado(char *linea)
{
	return strstr(linea, "\n");
}


/*
 * Devuelve la línea actual del archivo.
 * Debe ser guardada y posteriormente liberada.
 */
char *leer_linea(FILE *archivo)
{
	if (archivo == NULL)
		return NULL;
	size_t tmñ = LETRAS_LEIDAS_POR_ITERACION;
	char *linea = malloc(tmñ*sizeof(char));
	if (linea == NULL)
		return NULL;
	if (fgets(linea, (int)tmñ, archivo) == NULL) {
		free(linea);
		return NULL;
	}
	while (strlen(linea) + 1 == tmñ && strstr(linea, "\n") == NULL) {
		tmñ *= 2;
		char *nueva_linea = realloc(linea, tmñ);
		if (nueva_linea == NULL) {
			free(linea);
			return NULL;
		}
		linea = nueva_linea;
		char *siguiente_linea = &linea[strlen(linea)];
		siguiente_linea = fgets(siguiente_linea,
					(int)tmñ - (int)strlen(linea), archivo);
	}
	char *ultimo_char = &linea[strlen(linea) - 1];
	if (*ultimo_char == '\n')
		linea[strlen(linea) - 1] = '\0';
	return linea;
}




/* 
 * Convierte la primera coma en el string en '\0' y devuelve un puntero al
 * siguiente carácter.
 * Si no encuentra una coma, retorna NULL.
 */
char *desde_coma(char *string)
{
	char *coma = strstr(string, ",");
	if (coma == NULL)
		return NULL;
	*coma = '\0';
	return coma + 1;
}

/*
 * Devuelve el tipo del pokemon ingresado de formato string a formato int según
 * el enum que le corresponde definido en TP1_H_
 */
int texto_a_tipo(char *string)
{
	if (strcmp(string, TEXTO_ELEC) == 0)
		return TIPO_ELEC;
	if (strcmp(string, TEXTO_FUEG) == 0)
		return TIPO_FUEG;
	if (strcmp(string, TEXTO_PLAN) == 0)
		return TIPO_PLAN;
	if (strcmp(string, TEXTO_AGUA) == 0)
		return TIPO_AGUA;
	if (strcmp(string, TEXTO_FANT) == 0)
		return TIPO_FANT;
	if (strcmp(string, TEXTO_LUCH) == 0)
		return TIPO_LUCH;
	if (strcmp(string, TEXTO_NORM) == 0)
		return TIPO_NORM;
	if (strcmp(string, TEXTO_PSI) == 0)
		return TIPO_PSI;
	return ERROR;
}

struct pokemon *parsear_pokemon(char *linea)
{
	if (linea == NULL)
		return NULL;
	int longitud_linea = (int)strlen(linea) + 1;
	char linea_stack[longitud_linea];
	strcpy(linea_stack, linea);

	char *id = linea_stack;
	char *nombre = desde_coma(linea_stack);
	if (nombre == NULL)
		return NULL;
	char *tipo = desde_coma(nombre);
	if (tipo == NULL)
		return NULL;
	char *ataque = desde_coma(tipo);
	if (ataque == NULL)
		return NULL;
	char *defensa = desde_coma(ataque);
	if (defensa == NULL)
		return NULL;
	char *velocidad = desde_coma(defensa);
	if (velocidad == NULL)
		return NULL;

	int tipo_num = texto_a_tipo(tipo);
	if (tipo_num == ERROR)
		return NULL;

	struct pokemon *pokemon = malloc(sizeof(struct pokemon));
	if (pokemon == NULL)
		return NULL;
	pokemon->id = atoi(id);
	pokemon->nombre = malloc(sizeof(char) * (strlen(nombre) + 1));
	strcpy(pokemon->nombre, nombre);
	pokemon->tipo = tipo_num;
	pokemon->ataque = atoi(ataque);
	pokemon->defensa = atoi(defensa);
	pokemon->velocidad = atoi(velocidad);
	bool id_invalido = pokemon->id == 0;
	bool stats_invalidas = pokemon->ataque == 0 || pokemon->defensa == 0 || pokemon->velocidad == 0;
	if (id_invalido || stats_invalidas) {
		free(pokemon->nombre);
		free(pokemon);
		return NULL;
	}

	return pokemon;
}

/*
 * Añade el pokemon 'pokemon' al vector dinámico del tp1.
 * En caso de error, no hace nada.
 */
void añadir_tp1_dinamico(struct pokemon *pokemon, tp1_t *tp1)
{
	if (pokemon == NULL)
		return;
	struct pokemon *pokes_nuevos = realloc(
		tp1->pokemones, sizeof(struct pokemon) * (tp1->cantidad + 1));
	if (pokes_nuevos == NULL)
		return;
	tp1->pokemones = pokes_nuevos;
	tp1->pokemones[tp1->cantidad] = *pokemon;
	tp1->cantidad++;
}

/*
 * Devuelve un puntero a un tp1 sin pokemones.
 * Debe ser liberado usando tp1_destruir();
 */
tp1_t *crear_tp1() {
	tp1_t *tp1 = malloc(sizeof(struct tp1));
	if(tp1 == NULL)
		return NULL;
	tp1->pokemones = malloc(sizeof(struct pokemon));
	if (tp1->pokemones == NULL) {
		free(tp1);
		return NULL;
	}
	tp1->cantidad = 0;
	return tp1;
}

tp1_t *tp1_leer_archivo(const char *nombre) {
	FILE *archivo = fopen(nombre, "r");
	if (archivo == NULL) 
		return NULL;
	tp1_t *tp1 = crear_tp1();
	if (tp1 == NULL)
		return NULL;
	char *linea = leer_linea(archivo);
	while (linea != NULL) { 
		struct pokemon *pokemon = parsear_pokemon(linea);
		añadir_tp1_dinamico(pokemon, tp1);
		
		free(linea);
		if (pokemon != NULL)
			free(pokemon);
		linea = leer_linea(archivo);
	}
	free(linea);
	fclose(archivo);
	if (tp1->cantidad == 0) {
		tp1_destruir(tp1);
		return NULL;
	}
	return tp1;
}


void tp1_destruir(tp1_t *tp1)
{
	int i = 0;
	while(tp1->cantidad > 0) {
		free(tp1->pokemones[i].nombre);
		i++;
		if(tp1->cantidad > 0) tp1->cantidad--;
	}
	free(tp1->pokemones);
	free(tp1);
}

size_t tp1_cantidad(tp1_t *tp1)
{
	return tp1->cantidad;
}

/*
 * Dado dos strings, devuelve true si el primero viene primero en el alfabeto.
 * Si no, devuele false.
 */
bool primero_en_alfabeto(char *primero, char *segundo)
{
	if (strcmp(primero, segundo) < 0)
		return true;
	return false;
}

void ordenar_pokemon(struct pokemon *pokemones, int cantidad_pokemones)
{
	if (pokemones == NULL)
		return;
	for (int i = 0; i < cantidad_pokemones; i++) {
		for (int j = 0; j < cantidad_pokemones - 1; j++) {
			struct pokemon tmp;
			char *pokemon = pokemones[j].nombre;
			char *sig_pokemon = pokemones[j + 1].nombre;
			if (!primero_en_alfabeto(pokemon, sig_pokemon)) {
				tmp = pokemones[j];
				pokemones[j] = pokemones[j + 1];
				pokemones[j + 1] = tmp;
			}
		}
	}
}
