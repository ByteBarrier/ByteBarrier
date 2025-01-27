##
# Project Title
#
# @file
# @version 0.1

INCLUDES = -Isrc -Iincludes
SRCDIR = src/
SOURCES = $(SRCDIR)main.cpp $(SRCDIR)Arbol.cpp

all: main clean

main:
	@printf "Compilando el main\n"
	g++ -g $(SOURCES) $(INCLUDES) -o main.out
	@printf "Completada la compilación del main\n"

clean:
	
# end
