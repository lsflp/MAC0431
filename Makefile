#  Nomes: Gustavo Henrique Faustino Silva                   Números USP: 9298260
#         Isabela Blücher                                                9298170
#         Luís Felipe de Melo Costa Silva                                9297961

CC = gcc
CFLAGS = -Wall  -O3 -Ofast -pedantic  -fopenmp

OBJ = projeto.o

default: color.o ppmio.o projeto.o 
	$(CC) $(CFLAGS) *.o -o projeto -lm

projeto.o: code/projeto.c
	$(CC) $(CFLAGS) -ansi -c $^

ppmio.o: code/ppmio/ppmio.c code/ppmio/ppmio.h
	$(CC) $(CFLAGS) -ansi -c $^

color.o: code/color/color.c code/color/color.h
	$(CC) $(CFLAGS) -ansi -c $^

clean:
	$(RM) projeto
	$(RM) *.o
	find . -name "*.gch" -type f -delete