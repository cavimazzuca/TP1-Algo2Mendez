#include <stdio.h>
#include "src/tp1.h"
#define ERROR -1
#define ARCHIVO_PRUEBA_INEXISTENTE "ejemplos/asdkasjhfskladjhfksdfhksdf.csv"
#define ARCHIVO_PRUEBA_VACIO "ejemplos/vacio.csv"
#define ARCHIVO_PRUEBA_NORMAL "ejemplos/normal.csv"
#define ARCHIVO_PRUEBA_INVALIDO "ejemplos/sin_coma.csv"
#define ARCHIVO_STAT_INVALIDO "ejemplos/stat_invalida.csv"
#define ARCHIVO_TIPO_INVALIDO "ejemplos/tipo_invalido.csv"
#define ARCHIVO_LINEAS_VACIAS "ejemplos/lineas_vacias.csv"
#define ARCHIVO_PARA_GUARDAR "ejemplos/guardado.csv"

int main(int argc, char *argv[])
{
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_STAT_INVALIDO);
	if(tp1 == NULL)
		return ERROR;
	tp1_guardar_archivo(tp1, ARCHIVO_PARA_GUARDAR);
	tp1_destruir(tp1);
	
	//leer un archivo según el parámetro y hacer lo que corresponda según el enunciado

	return 0;
}
