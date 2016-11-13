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

/* Recebe o nome de um arquivo de imagem, efetua a leitura e devolve uma matriz
 * tridimensional referente à imagem. */
int ***readImage (char *archive);

/* A partir de uma matriz tridimensional que representa uma imagem, cria um 
 * arquivo .ppm e escreve a imagem nele. */ 
void writeImage (int ***img, int w, int h, char *archive);

/* Recebe uma matriz tridimensional e libera o espaço alocado para ela. */
void freeImage (int ***img, int w, int h);

/* Devolve um vetor de duas posições que representa o tamanho de uma imagem. 
 * A primeira posição é a largura e a segunda é a altura. */
int *getSize (char *archive);

/* Libera o espaço alocado pelo vetor do tamanho. */
int freeSize (int *size);

#endif