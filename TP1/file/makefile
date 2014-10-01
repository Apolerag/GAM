all: main

main: file_priorite_int.o main.o
	clang -o main file_priorite_int.o main.o

main.o: main.c file_priorite_int.o
	clang -o main.o -c main.c -W -Wall -ansi -pedantic

file_priorite_int.o: file_priorite_int.c base.h
	clang -o file_priorite_int.o -c file_priorite_int.c -W -Wall -ansi -pedantic

clean: 
	rm -rf *.o main