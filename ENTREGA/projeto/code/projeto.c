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
#include <omp.h>
#include "ppmio/ppmio.h"
#include "color/color.h"

int main (int argc, char **argv) {
    
    ppmImg M;
    int i, j, iter, MAX_ITER, N_PROCS;

    if (argc < 5) {
        printf("Uso: ./projeto <ARQUIVO> <SAIDA> <MAX_ITER> <N_PROCS>\n");
        return EXIT_FAILURE;
    }
    
    M = readImage (argv[1]);
    MAX_ITER = atoi (argv[3]);
    N_PROCS = atoi(argv[4]);

    omp_set_num_threads (N_PROCS);

    for (iter = 0; iter < MAX_ITER; iter++) {
        
        /* Percorre índices com soma par */
        /*#pragma omp parallel for shared(M) private(i, j) */
        for (i = 0; i < M->h-1; i+=2) {
            for (j = 0; j < M->w-1; j+=2) {
                /* Envia a cor para os pixels vizinhos. */
                sendColor(M, i, j);
                sendColor(M, i+1, j+1);
            }

            /* esse cara ficou de fora do for, pra evitar um if lá dentro
               ao checar o acesso do cara na diagonal dele */
            if(j == M->w - 1) 
                sendColor(M, i, j);
        }

        if(M->h % 2 == 0) {
            for(j = 0; j < M->w; j+= 2)
                sendColor(M, M->h - 1, j);
        }
            
        /* Percorre índices com soma ímpar */
        /*#pragma omp parallel for shared(M) private(i, j) */
        for (i = 0; i < M->h-1; i+=2) {
            for (j = 1; j < M->w; j+=2) {
                /* Envia a cor para os pixels vizinhos. */
                sendColor(M, i, j);
                sendColor(M, i+1, j-1);
            }

            if(j == M->w) 
                sendColor(M, i+1, j-1);
        } 

        if(M->h % 2 == 0) {
            for(j = 1; j < M->w; j+= 2)
                sendColor(M, M->h - 1, j);
        }
    }

    writeImage (M, argv[2]);
    freeImage (M);

    return EXIT_SUCCESS;
}
