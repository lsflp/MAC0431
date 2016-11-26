#  Nomes: Gustavo Henrique Faustino Silva                   Números USP: 9298260
#         Isabela Blücher                                                9298170
#         Luís Felipe de Melo Costa Silva                                9297961

C = gcc
CFLAGS = -Wall -ansi -Wno-unused-result -pedantic #-O2

OBJ = projeto.o

default: ppmimg.o projeto.o 
	$(CC) $(CFLAGS) *.o -o projeto

projeto.o: codigo/projeto.c
	$(CC) $(CFLAGS) -ansi -c $^

ppmimg.o: codigo/ppmimg/ppmimg.c codigo/ppmimg/ppmimg.h
	$(CC) $(CFLAGS) -ansi -c $^

clean:
	$(RM) projeto
	$(RM) *.o