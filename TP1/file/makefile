all: programme

programme: FilePrioriteVertex.o main.o
	gcc -o programme FilePrioriteVertex.o main.o

main.o: main.c FilePrioriteVertex.o
	gcc -o main.o -c main.c -W -Wall -ansi -pedantic

FilePrioriteVertex.o: FilePrioriteVertex.c base.h
	gcc -o FilePrioriteVertex.o -c FilePrioriteVertex.c -Wall -ansi -pedantic -std=c99

clean: 
	rm -rf *.o programme