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

ppmimg readImage (char *archive) {

    char c;
    int n, h, w, i, j, k;
    int ***img;
    FILE *in;

    in = fopen(archive, "r");
    
    /* Lendo o P3. */
    fscanf (in, "%c %d", &c, &n);
    fscanf (in, "%c", &c);

    /* Lendo as linhas de comentários. */
    fscanf (in, "%c", &c);
    do {
        do {
            fscanf (in, "%c", &c);
        } while (c != '\n');
        fscanf (in, "%c", &c);
    } while (c == '#');    

    n = ungetc (c, in);

    /* Lendo o tamanho da matriz. */
    fscanf (in, "%d %d", &w, &h);
    
    /* Lendo o 255. */
    fscanf (in, "%d", &n);

    /* Alocando a matriz. */
    img = malloc (w * sizeof (int *));

    for (i = 0; i < w; i++)
        img[i] = malloc (h * sizeof (int));

    for (i = 0; i < w; i++) {
        for (j = 0; j < h; j++) {
            img[i][j] = malloc (3 * sizeof (int));
        }
    }

    /* Lendo a imagem. */
    for (i = 0; i < w; i++) {
        for (j = 0; j < h; j++) {
            for (k = 0; k < 3; k++) {
                fscanf (in, "%d", &img[i][j][k]);
            }
        } 
    }

    fclose (in);

    ppmimg M = malloc (sizeof (ppmimg));

    M->img = img;
    M->w = w;
    M->h = h;

    return M;
}

void writeImage (ppmimg M, char *archive) {
    int i, j, k;
    FILE *out;

    out = fopen (archive, "w");

    fprintf(out, "P3\n");
    fprintf(out, "# Imagem gerada pela física alternativa.\n");
    fprintf(out, "%d %d\n255\n", M->w, M->h);

    for (i = 0; i < M->w; i++) {
        for (j = 0; j < M->h; j++) {
            for (k = 0; k < 3; k++) {
                fprintf(out, "%3d ", M->img[i][j][k]);
            }
            fprintf(out, "\n");
        }
    }

    fclose (out);
}

void freeImage (ppmimg M) {
    int i, j;

    for (i = 0; i < M->w; i++) {
        for (j = 0; j < M->h; j++) {
            free (M->img[i][j]);
        } 
    }

    for (i = 0; i < M->h; i++)
        free(M->img[i]);

    free(M->img);

    free(M);
}
