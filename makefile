compilar_pruebas:
	gcc -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g src/*.c pruebas_alumno.c
pruebas: compilar_pruebas
	valgrind -s --leak-check=full --track-origins=yes --show-leak-kinds=all ./a.out
