compilar_pruebas:
	gcc -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g src/*.c pruebas_alumno.c
pruebas: compilar_pruebas
	valgrind -s --leak-check=full --track-origins=yes --show-leak-kinds=all ./a.out
compilar:
	gcc -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g src/*.c main.c
valgrind: compilar
	valgrind -s --leak-check=full --track-origins=yes --show-leak-kinds=all ./a.out
main: compilar
	./a.out
