/******************************************************************************
 *  Nomes: Gustavo Henrique Faustino Silva                  Números USP: 9298260
 *         Isabela Blücher                                               9298170
 *         Luís Felipe de Melo Costa Silva                               9297961
 * 
 *  Arquivo:   color.c
 *  Descrição: É a biblioteca que implementa as funções de cores.
 ******************************************************************************/ 

#include "color.h"

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

int send (int neighbor, double color) {
    double n;
    int result;

    if (color < 0)
        color = -color;

    n = neighbor/256;
    n = (1-n)*color/4;
    result = (int) n*256;

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
    r = red/256;
    g = green/256;
    b = blue/256;

    angle = 2*PI*g;

    vec_r = getCoordinates(r, angle, 0);
    vec_b = getCoordinates(b, angle, 1);

    /* Para a componente vermelha */

    if(vec_r->x > 0) { /* Direita */
        if(i + 1 < M->w - 1) {
            red_n = M->img[i+1][j][0];
            M->img[i+1][j][0] = send(red_n, vec_r->x);
        }
    }
    else { /* Esquerda */
        if (i - 1 > 0) {
            red_n = M->img[i-1][j][0];
            M->img[i-1][j][0] = send(red_n, -vec_r->x);
        }    
    }
    if (vec_r->y > 0) { /* Baixo*/
        if (j + 1 < M->h - 1) {
            red_n = M->img[i][j+1][0];
            M->img[i][j+1][0] = send(red_n, vec_r->y);
        }    
    }
    else { /* Cima */
        if (j - 1 > 0) {
            red_n = M->img[i][j-1][0];
            M->img[i][j-1][0] = send(red_n, -vec_r->y);
        }    
    }

    /* Para a componente azul */

    if (vec_b->x < 0) { /* Direita */
        if (i + 1 < M->w - 1) {
            blue_n = M->img[i+1][j][2];
            M->img[i+1][j][2] = send(blue_n, vec_b->x);
        }    
    }
    else { /* Esquerda */
        if (i - 1 > 0) {
            blue_n = M->img[i-1][j][2];
            M->img[i-1][j][2] = send(blue_n, vec_b->x);
        }    
    }

    if (vec_r->y < 0) { /* Baixo */
        if (j + 1 < M->h - 1) {
            blue_n = M->img[i][j+1][2];
            M->img[i][j+1][2] = send(blue_n, vec_b->y); 
        }  
    }
    else { /* Cima */
        if (j - 1 > 0) {
            blue_n = M->img[i][j-1][2];
            M->img[i][j-1][2] = send(blue_n, vec_b->y);
        }
    }

    free(vec_r);
    free(vec_b);
}

void correctColor (ppmImg M, int i, int j) {
    int comp, new, dcorr;
    double color, coor;

    if (M->img[i][j][0] > 255)
        comp = 0;
    else if(M->img[i][j][1] > 255)
        comp = 1;
    else if(M->img[i][j][2] > 255)
        comp = 2;
    else
        return;

    color = M->img[i][j][comp]/256;
    coor = (double) (color-1)/4;
    dcorr = (int) coor*256;

    if (i + 1 < M->w - 1)
        if ((new = M->img[i+1][j][comp]+dcorr) <= 255)
            M->img[i+1][j][comp] = new;
    if (i - 1 > 0)
        if ((new = M->img[i-1][j][comp]+dcorr) <= 255)
            M->img[i-1][j][comp] = new;
    if (j + 1 < M->h - 1)
        if ((new = M->img[i][j+1][comp]+dcorr) <= 255)
            M->img[i][j+1][comp] = new;
    if (j - 1 > 0)
        if ((new = M->img[i][j-1][comp]+dcorr) <= 255)
            M->img[i][j-1][comp] = new;
}
