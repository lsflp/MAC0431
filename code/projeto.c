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
    return EXIT_SUCCESS;
}