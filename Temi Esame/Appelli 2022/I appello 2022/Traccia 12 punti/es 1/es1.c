/**
 * Appello del 27/01/2022 - Prova di programmazione (12 punti)
 *
 * Esercizio 1 (2 punti)
 *
 */

#include <stdio.h>
#include <stdlib.h>

void f(int **M, int r, int c, int ***M_out, int *r_out, int *c_out);
void printM(int **mat, int r, int c);

int main(int argc, char *argv[])
{
    int i;
    int r = 3, c = 3, r_out = 0, c_out = 0, **M_out;

    // Allochiamo la matrice di input della funzione f.
    int **M = (int **)malloc(sizeof(int *) * r);
    if (M == NULL)
        return -1;
    for (i = 0; i < r; i++)
    {
        M[i] = (int *)malloc(sizeof(int) * c);
        if (M[i] == NULL)
            return -1;
    }

    // Definiamo la Matrice M.
    M[0][0] = 1;
    M[0][1] = 2;
    M[0][2] = 3;

    M[1][0] = 4;
    M[1][1] = 0;
    M[1][2] = 9;

    M[2][0] = 7;
    M[2][1] = 8;
    M[2][2] = 9;

    printM(M, r, c);

    f(M, r, c, &M_out, &r_out, &c_out);

    printM(M_out, r_out, c_out);

    // Free M
    for (i = 0; i < r; i++)
    {
        free(M[i]);
    }
    free(M);

    // Free M_out
    for (i = 0; i < r_out; i++)
    {
        free(M_out[i]);
    }
    free(M_out);

    return 0;
}

void printM(int **mat, int r, int c)
{
    printf("Matrice:\n");

    for (int i = 0; i < r; i++)
    {
        printf("\t[");
        for (int j = 0; j < c - 1; j++)
        {
            printf("%d ", mat[i][j]);
        }
        printf("%d]\n", mat[i][c - 1]);
    }
}

void f(int **M, int r, int c, int ***M_out, int *r_out, int *c_out)
{
    int i, j, x, y;
    int *r_allowed, *c_allowed;

    // Allocazione vettori supplementari.
    r_allowed = (int *)malloc(sizeof(int) * r);
    c_allowed = (int *)malloc(sizeof(int) * c);
    // Controllo sul successo della malloc.
    if (r_allowed == NULL || c_allowed == NULL)
    {
        printf("Errore nell'allocazione dei vettori supplementari!\n");
        return;
    }
    // Inizializzazione vettori di supporto.
    for (i = 0; i < r; i++)
    {
        r_allowed[i] = 1;
    }
    for (i = 0; i < c; i++)
    {
        c_allowed[i] = 1;
    }

    // Scansiono matrice input e aggiorno i vettori di supporto.
    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            if (M[i][j] == 0)
            {
                r_allowed[i] = 0;
                c_allowed[j] = 0;
            }
        }
    }

    // Computo le dimensioni della matrice di output.
    *r_out = 0;
    *c_out = 0;
    for (i = 0; i < r; i++)
    {
        if (r_allowed[i])
            (*r_out)++;
    }
    for (i = 0; i < c; i++)
    {
        if (c_allowed[i])
            (*c_out)++;
    }

    // Alloco matrice di output.
    if ((*M_out = (int **)malloc(sizeof(int *) * (*r_out))) == NULL)
    {
        printf("Errore nell'allocazione della matrice di output!\n");
        return;
    }
    for (i = 0; i < (*r_out); i++)
    {
        if (((*M_out)[i] = (int *)malloc(sizeof(int) * (*c_out))) == NULL)
        {
            printf("Errore nell'allocazione della matrice di output!\n");
            return;
        }
    }

    x = 0;
    y = 0;
    // Completo la matrice di output con i valori corretti.
    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            if (r_allowed[i] == 1 && c_allowed[j] == 1)
            {
                (*M_out)[x][y] = M[i][j];
                y++;
                if (y == *c_out)
                {
                    y = 0;
                    x++;
                    if (x > *r_out)
                    {
                        printf("Errore! Sforato la dimensione allocata per la matrice di output!\n");
                        return;
                    }
                }
            }
        }
    }

    // Free dei vettori extra.
    free(r_allowed);
    free(c_allowed);
}
