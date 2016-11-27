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

#define PI 3.14159265

typedef struct {
	double x, y;
} *colorVec;

/* Recebe um inteiro entre 0 e 255 e retorna esse valor normatizado no intervalo
   [0, 1[ como um número real. */
double normatize (int color);

/* Recebe um número real no intervalo [0,1[ e retorna esse valor no intervalo 
   [0, 255[ como um número inteiro. */
int denormatize (double value);

/* Recebe a cor verde já normatizada e devolve o ângulo correspondente a essa 
   componente. */
double getAngle (double green);

/* Dados a intensidade da cor e o ângulo determinado pela cor verde, devolve as 
   coordenadas x e y do vetor que color representa. Precisa de um número que 
   representa a cor (0 para R e 1 para B). Depois de seu uso, deve-se liberar
   o ponteiro associado ao valor da devolução. */
colorVec getCoordinates (double color, double angle, int n);

/* Determina o quanto de color será transferido para o vizinho, dado sua atual
   intensidade (neighboor). */
double transfer (double neighboor, double color);

/* Caso um pixel exceda o valor 1, o excedente que será transferido para cada
   vizinho é devolvido por essa função. */
double correct (double color);

#endif