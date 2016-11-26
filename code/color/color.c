/******************************************************************************
 *  Nomes: Gustavo Henrique Faustino Silva                  Números USP: 9298260
 *         Isabela Blücher                                               9298170
 *         Luís Felipe de Melo Costa Silva                               9297961
 * 
 *  Arquivo:   color.c
 *  Descrição: É a biblioteca que implementa as funções de cores.
 ******************************************************************************/ 

#include "color.h"

double normatize (int color) {
    return (double) color/256;
}

int denormatize (double value) {
    return (int) (value*256);
}

double getAngle (double green) {
    return 2*PI*green;
}

colorVec getCoordinates (double color, double angle, int n) {
    colorVec c = malloc (sizeof (colorVec));
    if (n) {
        c->x = -color*sin(angle);
        c->y = -color*cos(angle);
    }
    else {
        c->x = color*sin(angle);
        c->y = color*cos(angle); 
    }        
    return c;
}

double transfer (double neighboor, double color) {
    return ((1-neighboor)*color)/4;
}

double correct (double color) {
    double excess = color-1;
    return excess/4;
}