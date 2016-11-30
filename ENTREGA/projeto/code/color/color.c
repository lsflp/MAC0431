/******************************************************************************
 *  Nomes: Gustavo Henrique Faustino Silva                  Números USP: 9298260
 *         Isabela Blücher                                               9298170
 *         Luís Felipe de Melo Costa Silva                               9297961
 * 
 *  Arquivo:   color.c
 *  Descrição: É a biblioteca que implementa as funções de cores.
 ******************************************************************************/ 

#include "color.h"

colorVec getCoordinates (double color, double angle) {
    colorVec c = malloc (sizeof(colorVec));    
    c->x = color*sin(angle);
    c->y = color*cos(angle);      
    return c;
}

int send (int neighbor, double color) {
    double n;
    int result;

    if (color < 0)
        color = -color;

    n = (double) neighbor/256;
    n = ((double) (1-n)*color)/4;
    result = (int) (n*256);
    
    return result;
}

void sendColor (ppmImg M, int i, int j) {
    
    colorVec vec_r, vec_b;
    double r, g, b;
    double angle, newAngle, transfer;
    int red_n, blue_n;

    /* normatizar cores */
    r = (double) M->img[i][j][0]/256;
    g = (double) M->img[i][j][1]/256;
    b = (double) M->img[i][j][2]/256;

    angle = DOISPI*g;

    vec_r = getCoordinates(r, angle);
    vec_b = getCoordinates(b, angle);

    /* Para a componente vermelha */

    if(vec_r->x > 0) { /* Direita */
        if(i + 1 < M->h - 1) {
            red_n = M->img[i+1][j][0];
            transfer = send(red_n, vec_r->x);
            M->img[i+1][j][0] += transfer;
            if (i < M->h - 1) M->img[i][j][0] -= transfer;
        }
    }
    else { /* Esquerda */
        if (i - 1 > 0) {
            red_n = M->img[i-1][j][0];
            transfer = send(red_n, vec_r->x);
            M->img[i-1][j][0] += transfer;
            if (i > 0) M->img[i][j][0] -= transfer;
        }    
    }
    if (vec_r->y > 0) { /* Baixo*/
        if (j + 1 < M->w - 1) {
            red_n = M->img[i][j+1][0];
            transfer = send(red_n, vec_r->y);
            M->img[i][j+1][0] += transfer;
            if (j < M->w - 1) M->img[i][j][0] -= transfer;
        }    
    }
    else { /* Cima */
        if (j - 1 > 0) {
            red_n = M->img[i][j-1][0];
            transfer = send(red_n, vec_r->y);
            M->img[i][j-1][0] += transfer;
            if (j > 0) M->img[i][j][0] -= transfer;
        }    
    }

    /* Para a componente azul */

    if (vec_b->x < 0) { /* Direita */
        if (i + 1 < M->h - 1) {
            blue_n = M->img[i+1][j][2];
            transfer = send(blue_n, -vec_b->x);
            M->img[i+1][j][2] += transfer;
            if (i < M->h - 1) M->img[i][j][2] -= transfer;
        }    
    }
    else { /* Esquerda */
        if (i - 1 > 0) {
            blue_n = M->img[i-1][j][2];
            transfer = send(blue_n, -vec_b->x);
            M->img[i-1][j][2] += transfer;
            if (i > 0) M->img[i][j][2] -= transfer;
        }    
    }

    if (vec_r->y < 0) { /* Baixo */
        if (j + 1 < M->w - 1) {
            blue_n = M->img[i][j+1][2];
            transfer = send(blue_n, -vec_b->y);
            M->img[i][j+1][2] += transfer;
            if (j < M->w - 1) M->img[i][j][2] -= transfer; 
        }  
    }
    else { /* Cima */
        if (j - 1 > 0) {
            blue_n = M->img[i][j-1][2];
            transfer = send(blue_n, -vec_b->y);
            M->img[i][j-1][2] += transfer;
            if (j > 0) M->img[i][j][2] -= transfer;
        }
    }

    /* Atualizando o verde. */
    if (i > 0 && j > 0 && i < M->h - 1 && j < M->w - 1) {
        newAngle = atan2 ((double) M->img[i][j][0], (double) M->img[i][j][2]);
        angle += newAngle;
        /* Para não estourar. */
        while (angle > DOISPI)
            angle -= DOISPI;
        angle /= DOISPI;
        M->img[i][j][1] = (int) (angle*256);
    }

    free(vec_r);
    free(vec_b);
}
