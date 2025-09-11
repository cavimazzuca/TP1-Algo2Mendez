#include <stdio.h>
#include "pa2m.h"
#include "src/tp1.h"

#define ARCHIVO_PRUEBA_INEXISTENTE "ejemplos/asdkasjhfskladjhfksdfhksdf.csv"
#define ARCHIVO_PRUEBA_VACIO "ejemplos/vacio.csv"
#define ARCHIVO_PRUEBA_NORMAL "ejemplos/normal.csv"
#define ARCHIVO_PRUEBA_INVALIDO "ejemplos/sin_coma.csv"
#define ARCHIVO_STAT_INVALIDO "ejemplos/stat_invalida.csv"
#define ARCHIVO_TIPO_INVALIDO "ejemplos/tipo_invalido.csv"
#define ARCHIVO_LINEAS_VACIAS "ejemplos/lineas_vacias.csv"
#define ARCHIVO_GUARDADO "ejemplos/guardado.csv"
#define ARCHIVO_REPETIDOS "ejemplos/repetidos.csv"

void tp1_poke_repetido_no_cuenta()
{
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_REPETIDOS);
	pa2m_afirmar(tp1_cantidad(tp1) == 2, "Ignora pokemones repetidos");
	if (tp1 != NULL) {
		tp1_destruir(tp1);
	}
}

void tp1_guardar_tp_prueba_invalidos()
{
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_STAT_INVALIDO);
	tp1 = tp1_guardar_archivo(tp1, ARCHIVO_GUARDADO);
	tp1_t *tp1_2 = tp1_leer_archivo(ARCHIVO_GUARDADO);
	pa2m_afirmar(tp1_cantidad(tp1_2) == 4, "Guarda solo pokemones válidos");
	if (tp1 != NULL) {
		tp1_destruir(tp1);
	}
	if (tp1_2 != NULL) {
		tp1_destruir(tp1_2);
	}
}

void tp1_guardar_tp_prueba_cantidad()
{
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_NORMAL);
	tp1 = tp1_guardar_archivo(tp1, ARCHIVO_GUARDADO);
	tp1_t *tp1_2 = tp1_leer_archivo(ARCHIVO_GUARDADO);
	pa2m_afirmar(tp1_cantidad(tp1_2) == 5, "La cantidad de pokemones es correcta");
	if (tp1 != NULL) {
		tp1_destruir(tp1);
	}
	if (tp1_2 != NULL) {
		tp1_destruir(tp1_2);
	}
	
}

void tp1_guardar_tp_inexistente_devuelve_null()
{
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_INEXISTENTE);
	tp1 = tp1_guardar_archivo(tp1, ARCHIVO_GUARDADO);
	pa2m_afirmar(tp1 == NULL, "Guardar un tp NULL devuelve NULL");
	if (tp1 != NULL) {
		tp1_destruir(tp1);
	}
	
}

void tp1_poke_tipo_invalido_no_cuenta()
{
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_TIPO_INVALIDO);
	pa2m_afirmar(tp1_cantidad(tp1) == 4, "Pokemon con tipos inválidos no se leen");
	if (tp1 != NULL) {
		tp1_destruir(tp1);
	}
}

void tp1_poke_stat_invalido_no_cuenta()
{
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_STAT_INVALIDO);
	pa2m_afirmar(tp1_cantidad(tp1) == 4, "Pokemon con stats inválidos no se leen");
	if (tp1 != NULL) {
		tp1_destruir(tp1);
	}
}

void tp1_lineas_vacias_no_cuentan()
{
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_LINEAS_VACIAS);
	pa2m_afirmar(tp1 != NULL, "Lineas vacías en el archivo son ignoradas");
	if (tp1 != NULL) {
		tp1_destruir(tp1);
	}
}

void tp1_poke_cantidades_correctas()
{
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_NORMAL);
	pa2m_afirmar(tp1_cantidad(tp1) == 5, "La cantidad de pokemones es correcta");
	if (tp1 != NULL) {
		tp1_destruir(tp1);
	}
}

void tp1_leer_archivo_devuelve_no_null()
{
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_NORMAL);
	pa2m_afirmar(tp1 != NULL, "Abrir un archivo bueno NO devuelve NULL");
	if (tp1 != NULL) {
		
		tp1_destruir(tp1);
		
	}
}

void tp1_leer_archivo_devuelve_null_cuando_el_archivo_es_inválido()
{
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_INVALIDO);
	pa2m_afirmar(tp1 == NULL, "Abrir un archivo inválido devuelve NULL");
	if (tp1 != NULL)
		tp1_destruir(tp1);
}

void tp1_leer_archivo_devuelve_null_cuando_el_archivo_esta_vacío()
{
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_VACIO);
	pa2m_afirmar(tp1 == NULL, "Abrir un archivo vacío devuelve NULL");
	if (tp1 != NULL)
		tp1_destruir(tp1);
}

void tp1_leer_archivo_devuelve_null_cuando_el_archivo_no_existe()
{
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_INEXISTENTE);
	pa2m_afirmar(tp1 == NULL, "Abrir un archivo inexistente devuelve NULL");
	if (tp1 != NULL)
		tp1_destruir(tp1);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de lectura de archivos");
	tp1_leer_archivo_devuelve_null_cuando_el_archivo_no_existe();
	tp1_leer_archivo_devuelve_null_cuando_el_archivo_esta_vacío();
	tp1_leer_archivo_devuelve_null_cuando_el_archivo_es_inválido();
	tp1_leer_archivo_devuelve_no_null();
	tp1_poke_cantidades_correctas();
	tp1_lineas_vacias_no_cuentan();
	tp1_poke_stat_invalido_no_cuenta();
	tp1_poke_tipo_invalido_no_cuenta();
	tp1_poke_repetido_no_cuenta();
	pa2m_nuevo_grupo("Pruebas de guardado de archivos");
	tp1_guardar_tp_inexistente_devuelve_null();
	tp1_guardar_tp_prueba_cantidad();
	tp1_guardar_tp_prueba_invalidos();

	return pa2m_mostrar_reporte();
}
