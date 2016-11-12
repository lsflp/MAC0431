/******************************************************************************
 *  Nomes: Gustavo Henrique Faustino Silva                  Números USP: 9298260
 *         Isabela Blücher                                               9298170
 *         Luís Felipe de Melo Costa Silva                               9297961
 * 
 *  Arquivo:   ppmio.c
 *  Descrição: É a biblioteca para manipulação de arquivos .ppm .Possui funções 
 *             de leitura e escrita, por exemplo.
 ******************************************************************************/ 

#include "ppmio.h"

int **readImage (char *archive) {

    char c;
    int n, h, w, i, j, k;
    int ***img;
    FILE *in;

    in = fopen(archive, "r");
    
    /* Lendo o P3. */
    fscanf (in, "%c %d", &c, &n);
    
    /* Lendo as linhas de comentários. */
    fscanf (in, "%c", &c);
    while (1) {
        if (c == '#') {
            do {
                fscanf (in, "%c", &c);
            }while (c != 'n')
        }
        else 
            break; 
    }
    
    /* Lendo o tamanho da matriz. */
    fscanf (in, "%d %d", &h, &w);
    
    /* Lendo o 255. */
    fscanf (in, "%d", &n);
    
    /* Alocando a matriz. */
    img = malloc (h * sizeof (int *));

    for (i = 0; i < h; i++)
        img[i] = malloc (w * sizeof (int));

    for (i = 0; i < h; i++) {
        for (j = 0; j < w; j++) {
            img[i][j] = malloc (3 * sizeof (int));
        }
    }

    /* Lendo a imagem. */
    for (i = 0; i < h; i++) {
        for (j = 0; j < w; j++) {
            for (k = 0; k < 3; k++) {
                fscanf (in, "%d", img[i][j][k]);
            }
        } 
    }

    fclose (in);

    return img;
}

void writeImage (int ***img, char *archive) {
    int h = sizeof(img);
    int w = sizeof(img[0]);
    int i, j, k;
    FILE *out = fopen (archive, "w");

    fprintf(out, "P3\n");
    fprintf(out, "# Imagem gerada pela física alternativa.");
    fprintf(out, "%d %d\n255\n", h, w);

    for (i = 0; i < h; i++) {
        for (j = 0; j < w; j++) {
            for (k = 0; k < 3; k++) {
                fprintf(out, "%3d ", img[i][j][k]);
            }
            fprintf(out, "   ");
        }
        fprintf(out, "\n");
    }

    fclose (out);
}

void freeMatrix (int ***img) {
    int h = sizeof(img);
    int w = sizeof(img[0]);

    int i, j;

    for (i = 0; i < h; i++) {
        for (j = 0; j < w; j++) {
            free (img[i][j]);
        } 
    }

    for (i = 0; i < h; i++)
        free(img[i]);

    free (img);
}

