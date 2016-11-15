/******************************************************************************
 *  Nomes: Gustavo Henrique Faustino Silva                  Números USP: 9298260
 *         Isabela Blücher                                               9298170
 *         Luís Felipe de Melo Costa Silva                               9297961
 * 
 *  Arquivo:   ppmio.h
 *  Descrição: É a biblioteca para manipulação de arquivos .ppm .Possui funções 
 *             de leitura e escrita, por exemplo.
 ******************************************************************************/ 

#ifndef PPMIO_H
#define PPMIO_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int ***img;
    int w, h;
} *ppmimg;

/* Recebe o nome de um arquivo de imagem, efetua a leitura e devolve uma struct 
 * referente à imagem. */
ppmimg readImage (char *archive);

/* A partir de uma struct com uma matriz tridimensional que representa uma 
 * imagem, cria um arquivo .ppm e escreve a imagem nele. */ 
void writeImage (ppmimg M, char *archive);

/* Recebe uma struct com que representa a imagem e libera o espaço alocado para 
 * ela. */
void freeImage (ppmimg M);

#endif