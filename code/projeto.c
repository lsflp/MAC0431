/******************************************************************************
 *  Nomes: Gustavo Henrique Faustino Silva                  Números USP: 9298260
 *         Isabela Blücher                                               9298170
 *         Luís Felipe de Melo Costa Silva                               9297961
 * 
 *  Arquivo:    projeto.c
 *  Compilação: make
 *  Descrição:  Implementa o Física Alternativa
 ******************************************************************************/ 

#include <stdio.h>
#include <stdlib.h>
#include "ppmio/ppmio.h"
#include "color/color.h"

int main (int argc, char **argv) {
    
    ppmImg M;
    int i, j, k, l, iter, MAX_ITER;

    if (argc < 2) {
        printf("Uso: ./projeto <ARQUIVO> <SAÍDA> <MAX_ITER>\n");
        return EXIT_FAILURE;
    }
    
    M = readImage (argv[1]);
    MAX_ITER = atoi (argv[3]);

    for (iter = 0; iter < MAX_ITER; iter++) {
        
        /* Percorre índices com soma par */
        for (i = 0; i < M->w; i+=2) {
            for (j = 0; j < M->h; j+=2) {
                /* Envia a cor para os pixels vizinhos. */
                sendColor(M, i, j);
            }
        }

        /* Percorre índices com soma ímpar */
        for (k = 1; k < M->w; k+=2) {
            for (l = 1; l < M->h; l+=2) {
                /* Envia a cor para os pixels vizinhos. */
                sendColor(M, k, l);
            }
        }
    }

    writeImage (M, argv[2]);
    freeImage (M);

    return EXIT_SUCCESS;
}