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

double transfer (double neighbor, double color) {
    return ((1-neighbor)*color)/4;
}

double correct (double color) {
    double excess = color-1;
    return excess/4;
}

int send (int neighbor, int color) {
    double n;
    int result;

    n = normatize(neighbor);
    n = transfer(n, color);
    result = denormatize(n);
}

void sendColor (int i, int j, int n) {
    int red_n, blue_n;
    double r, g, b;
    double angle;
    colorVec r, b;

    vec_r = malloc (sizeof (colorVec));
    vec_b = malloc (sizeof (colorVec));

    red = matrix[i][j][0];
    green = matrix[i][j][1];
    blue = matrix[i][j][2];

    /* normatizar cores */
    r = normatize(red);
    g = normatize(green);
    b = normatize(blue);

    angle = getAngle(g);
    vec_r = getCoordinates(r, angle, 0);
    vec_b = getCoordinates(b, angle, 1);

    /* olhamos o vermelho */
    if(vec_r->x < 0) { /* direita */
        red_n = matrix[i+1][j][0];
        matrix[i+1][j][0] = send(red_n, r);
    }
    else { /* esquerda */
        red_n = matrix[i-1][j][0];
        matrix[i-1][j][0] = send(red_n, r);
    }

    if (vec_r->y < 0) { /* cima */
        red_n = matrix[i][j+1][0];
        matrix[i][j+1][0] = send(red_n, r);
    }
    else { /* baixo */
        red_n = matrix[i][j-1][0];
        matrix[i][j-1][0] = send (red_n, r);
    }

    /* olhamos o azul */
    if(vec_b->x > 0) { /* direita */
        blue_n = matrix[i+1][j][2];
        matrix[i+1][j][2] = send(blue_n, b);
    }
    else { /* esquerda */
        blue_n = matrix[i-1][j][2];
        matrix[i-1][j][2] = send(blue_n, b);
    }

    if (vec_r->y > 0) { /*cima*/
        blue_n = matrix[i][j+1][2];
        matrix[i][j+1][2] = send(blue_n, b);
    }
    else {
        blue_n = matrix[i][j-1][2];
        matrix[i][j-1][2] = send(blue_n, b);
    }
}