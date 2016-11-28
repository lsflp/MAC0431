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

int inBorder (ppmImg M, int i, int j) {
    if (i <= 0 || i >= (M->w)-1)
        return 1;
    if (j <= 0 || j >= (M->h)-1)
        return 1;
    return 0;
}

int send (int neighbor, double color) {
    double n;
    int result;

    if (color < 0)
        color = -color;

    n = normatize(neighbor);
    n = transfer(n, color);
    result = denormatize(n);

    return result;
}

void sendColor (ppmImg M, int i, int j) {
    
    colorVec vec_r, vec_b;
    double r, g, b;
    double angle;
    int red_n, blue_n, red, green, blue;

    red = M->img[i][j][0];
    green = M->img[i][j][1];
    blue = M->img[i][j][2];

    /* normatizar cores */
    r = normatize(red);
    g = normatize(green);
    b = normatize(blue);

    angle = getAngle(g);

    vec_r = malloc (sizeof (colorVec));
    vec_b = malloc (sizeof (colorVec));

    vec_r = getCoordinates(r, angle, 0);
    vec_b = getCoordinates(b, angle, 1);

    /* Para a componente vermelha */

    if(vec_r->x > 0) { /* Direita */
        if (!inBorder(M, i+1, j)) {
            red_n = M->img[i+1][j][0];
            M->img[i+1][j][0] = send(red_n, vec_r->x);
        }    
    }
    else { /* Esquerda */
        if (!inBorder(M, i-1, j)) {
            red_n = M->img[i-1][j][0];
            M->img[i-1][j][0] = send(red_n, -vec_r->x);
        }    
    }
    if (vec_r->y > 0) { /* Baixo*/
        if (!inBorder(M, i, j+1)) {
            red_n = M->img[i][j+1][0];
            M->img[i][j+1][0] = send(red_n, vec_r->y);
        }    
    }
    else { /* Cima */
        if (!inBorder(M, i, j-1)) {
            red_n = M->img[i][j-1][0];
            M->img[i][j-1][0] = send(red_n, -vec_r->y);
        }    
    }

    /* Para a componente azul */

    if (vec_b->x < 0) { /* Direita */
        if (!inBorder(M, i+1, j)) {
            blue_n = M->img[i+1][j][2];
            M->img[i+1][j][2] = send(blue_n, vec_b->x);
        }    
    }
    else { /* Esquerda */
        if (!inBorder(M, i-1, j)) {
            blue_n = M->img[i-1][j][2];
            M->img[i-1][j][2] = send(blue_n, vec_b->x);
        }    
    }

    if (vec_r->y < 0) { /* Baixo */
        if (!inBorder(M, i, j+1)) {
            blue_n = M->img[i][j+1][2];
            M->img[i][j+1][2] = send(blue_n, vec_b->y); 
        }  
    }
    else { /* Cima */
        if (!inBorder(M, i, j-1)) {
            blue_n = M->img[i][j-1][2];
            M->img[i][j-1][2] = send(blue_n, vec_b->y);
        }
    }

    free(vec_r);
    free(vec_b);
}