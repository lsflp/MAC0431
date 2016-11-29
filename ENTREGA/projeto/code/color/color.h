/******************************************************************************
 *  Nomes: Gustavo Henrique Faustino Silva                  Números USP: 9298260
 *         Isabela Blücher                                               9298170
 *         Luís Felipe de Melo Costa Silva                               9297961
 * 
 *  Arquivo:   color.h
 *  Descrição: É a biblioteca para manipulação de cores. Tem uma estrutura que 
 *             define o vetor da componente das cores e funções que fazem os 
 *             cálculos referentes às cores.
 ******************************************************************************/ 

#ifndef COLOR_H
#define COLOR_H

#include <stdlib.h>
#include <math.h>
#include "../ppmio/ppmio.h"

#define PI 3.14159265

typedef struct {
   double x, y;
} *colorVec;

/* Dados a intensidade da cor e o ângulo determinado pela cor verde, devolve as 
   coordenadas x e y do vetor que color representa. */
colorVec getCoordinates (double color, double angle);

/* Dado um valor inteiro que representa uma componente de cor do vizinho e um 
   valor real que representa uma componente de cor, devolvemos a interação entre
   as componentes, de acordo com o enunciado.*/
int send (int neighbor, double color);

/* Dado um pixel (i, j) na matriz M->img, transferimos as cores para os 
   vizinhos. */
void sendColor (ppmImg M, int i, int j);

/* Corrige a cor, caso a componente tenha sido excedida, transferindo para
   os vizinhos somente se não for causar estouro. */
void correctColor (ppmImg M, int i, int j);

#endif
