CFLAGS = -c -g -Wall -pedantic
GL_INCLUDE    = -I/usr/include/GL
GL_LIBDIR    = -L. -L/usr/X11R6/lib
GL_LIBRARIES = -lglut -lGL -lm -lGLU -lXmu -lXext -lXi -lX11
CC = clang
OS = "unknown"
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
$$$
EXEC = tpga3

# Add objectiveC library for MacOSX.
ifneq ($(strip $(shell $(CC) -v 2>&1 | grep -i "Apple")),)
 GL_INCLUDE    = -I/usr/X11R6/include
 GL_LIBRARIES += -lobjc
 BROWSER = dillo
 OS = "osx"
endif
# Nothing to be done for Linux :o)
ifneq ($(strip $(shell $(CC) -v 2>&1 | grep -i "Linux")),)
 OS = "linux"
 BROWSER = mozilla
endif

all: clean $(EXEC)

sujet:
	acroread *.pdf&

job: all
	./$(EXEC) -1 -ores.txt && firefox DOX/html/index.html

$(EXEC): $(OBJ)
	$(CC) $(GL_LIBDIR) $(OBJ) $(GL_LIBRARIES) -o $@

%.o: %.c %.h
	$(CC) $(GL_INCLUDE) $(CFLAGS) $<

#
clean:
	@echo "operating system = $(OS)"
	rm -rf *.o DOX

veryclean: clean
	rm -rf $(EXEC)

dox: 
	rm -rf DOX
	doxygen main.dox
#

