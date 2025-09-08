#include <stdio.h>
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

int main(int argc, char *argv[])
{
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_NORMAL);
	if(tp1 == NULL)
		return ERROR;
	tp1_t *tp1_2 = tp1_leer_archivo(ARCHIVO_PRUEBA_NORMAL_2);
	if(tp1_2 == NULL)
		return ERROR;
	tp1_t *tp_unido = tp1_union(tp1,tp1_2);
	if(tp_unido == NULL)
		return ERROR;

	tp1_guardar_archivo(tp1,"ejemplos/guardado.csv");
	tp1_guardar_archivo(tp1_2,"ejemplos/guardado2.csv");
	tp1_guardar_archivo(tp_unido,"ejemplos/guardado3.csv");
	tp1_destruir(tp1);
	tp1_destruir(tp1_2);
	tp1_destruir(tp_unido);
	//leer un archivo según el parámetro y hacer lo que corresponda según el enunciado

	return 0;
}
