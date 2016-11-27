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
    
    /*ppmimg M;*/

    int i, k;
    colorVec c;
    double j, angle, red = 0.703125, redx, blue = 0.171875, green = 0.3984375;

    if (argc < 2) {
        printf("Uso: ./projeto <ARQUIVO>\n");
        return EXIT_FAILURE;
    }
    
    angle = getAngle (green);
    printf("%f\n", angle);
    c = getCoordinates (red, angle, 0);
    printf("(%f, %f)\n", c->x, c->y);
    free(c);
    c = getCoordinates (blue, angle, 1);
    printf("(%f, %f)\n", c->x, c->y);
    free(c);
    printf("%f\n", transfer (0.046875, red));
    printf("%f\n", correct(1.2));
    
    /*M = readImage (argv[1]);
    writeImage (M, "new.ppm");
    freeImage (M); */

    for (ticks = 0; ticks < MAX_TICKS; ticks++) {
        /* percorre índices pares */
        for (i = 0; i < /*tamanho horizontal da matriz*/; i+=2) {
            for (j = 0; j < /*tamanho vertical da matriz*/; j+=2) {
                sendColor(i, j, n);
            }
        }

        for (k = 1; k < /*tamanho horizontal da matriz*/; k+=2) {
            for (l = 1; l < /*tamanho vertical da matriz*/; l+=2) {
                sendColor(k, l, n);
            }
        }
    }
    return EXIT_SUCCESS;
}