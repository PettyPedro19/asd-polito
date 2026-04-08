/*
 * Politecnico di Torino — 03AAXOA Algoritmi e Strutture Dati
 * Lab 02 — Esercizio 2: Allocazione di matrici
 *
 * Autore : Marco Pedron
 * Data   : 31/03/2026
 */

/* =========================================================
 * LIBRERIE
 * ========================================================= */
#include <stdio.h>
#include <stdlib.h>

/* =========================================================
 * COSTANTI E TIPI
 * ========================================================= */
#define FILENAME "mat.txt"

/* =========================================================
 * DICHIARAZIONI FUNZIONI
 * ========================================================= */

int **malloc2dR(int nr, int nc, FILE *fileP);
void malloc2dP(int ***mtrx, int nr, int nc, FILE *fileP);
void separa(int **mat, int nr, int nc, int **white, int **black, int *bc, int *wc);

/* =========================================================
 * MAIN
 * ========================================================= */

int main(int argc, char *argv[])
{
    FILE *fin;
    int nr, nc, i, j;
    char opt;
    int **matrix, *white, *black, wc = 0, bc = 0;

    // Open file containing matrix
    if ((fin = fopen(FILENAME, "r")) == NULL)
    {
        printf("Error while opening file %s!\nClosing program.", FILENAME);
        return -1;
    }

    // read file first row to get #rows and cols.
    fscanf(fin, "%d", &nr);
    fscanf(fin, "%d", &nc);
    printf("Reading matrix:\nnr = %d, nc = %d\n", nr, nc);

    // Choose how to read matrix.
    printf("\n\nChoose allocation function:\na) malloc2dR();\nb) malloc2dP();\n\n>>");
    scanf("%c", &opt);

    switch (opt)
    {
    case 'a':
        printf("You chose \'malloc2dR()\'.\n");
        matrix = malloc2dR(nr, nc, fin);

        // Print matrix
        for (i = 0; i < nr; i++)
        {
            printf("[");
            for (j = 0; j < nc; j++)
            {
                printf("%d ", matrix[i][j]);
            }
            printf("]\n");
        }

        break;

    case 'b':
        printf("You chose \'malloc2dP()\'.\n");
        malloc2dP(&matrix, nr, nc, fin);

        // Print matrix
        for (i = 0; i < nr; i++)
        {
            printf("[");
            for (j = 0; j < nc; j++)
            {
                printf("%d ", matrix[i][j]);
            }
            printf("]\n");
        }
        break;

    default:
        printf("Error!\nClosing program.\n");
        return -1;
        break;
    }

    separa(matrix, nr, nc, &white, &black, &bc, &wc);

    printf("White: [");
    for (i = 0; i < wc; i++)
    {
        printf("%d ", white[i]);
    }
    printf("].\n\n");

    printf("Black: [");
    for (i = 0; i < bc; i++)
    {
        printf("%d ", black[i]);
    }
    printf("].\n\n");

    // free matrix
    for (i = 0; i < nr; i++)
    {
        free(matrix[i]);
    }
    free(matrix);

    free(black);
    free(white);
    fclose(fin);

    return 0;
}

/* =========================================================
 * IMPLEMENTAZIONI
 * ========================================================= */
int **malloc2dR(int nr, int nc, FILE *fileP)
{
    int **mat;
    int i, j;

    // Allocation.
    mat = (int **)malloc(nr * sizeof(int *));
    for (i = 0; i < nr; i++)
    {
        mat[i] = (int *)malloc(nc * sizeof(int));
    }

    // Writing matrix.
    for (i = 0; i < nr; i++)
    {
        for (j = 0; j < nc; j++)
        {
            fscanf(fileP, "%d", &mat[i][j]);
        }
    }

    return mat;
}
void malloc2dP(int ***mtrx, int nr, int nc, FILE *fileP)
{
    int i, j;

    // Allocation.
    *mtrx = (int **)malloc(nr * sizeof(int *));
    for (i = 0; i < nr; i++)
    {
        (*mtrx)[i] = (int *)malloc(nc * sizeof(int));
    }

    // Writing matrix.
    for (i = 0; i < nr; i++)
    {
        for (j = 0; j < nc; j++)
        {
            fscanf(fileP, "%d", &(*mtrx)[i][j]);
        }
    }
}
void separa(int **mat, int nr, int nc, int **white, int **black, int *bc, int *wc)
{
    int i, j;

    *white = malloc(((nr * nc) / 2) * sizeof(int));
    if (((nr * nc) % 2) == 1)
    {
        *black = malloc(((nr * nc) / 2 + 1) * sizeof(int));
    }
    else
    {
        *black = malloc(((nr * nc) / 2) * sizeof(int));
    }

    for (i = 0; i < nr; i++)
    {
        for (j = 0; j < nc; j++)
        {
            if (((i + j) % 2) == 0)
            {
                (*black)[*bc] = mat[i][j];
                (*bc)++;
            }
            else
            {
                (*white)[*wc] = mat[i][j];
                (*wc)++;
            }
        }
    }
}