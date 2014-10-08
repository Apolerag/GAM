CC=clang
CCFLAGS=-c -Wall -ansi -pedantic

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
EXEC = programme.exe

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ)  -o $@

%.o: %.cpp %.h
	$(CC) $(CCFLAGS) $<

clean:
	rm -rf *.o *.exe