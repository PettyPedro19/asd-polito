#include <stdio.h>
#include <stdlib.h>

void f(int **M, int r, int c, int k, int ***M_out);
void printM(int **M, int r, int c);

int main(int argc, char *argv[])
{
    int i, j;
    int **M, r = 5, c = 4, k = 2, **M_out;

    M = (int **)malloc(r * sizeof(int *));
    if (M == NULL)
    {
        printf("Cannot allocate memory!\n");
        return -1;
    }
    for (i = 0; i < r; i++)
    {
        M[i] = (int *)malloc(c * sizeof(int));
        if (M[i] == NULL)
        {
            printf("Cannot allocate memory!\n");
            return -1;
        }
    }

    M[0][0] = 1;
    M[0][1] = 2;
    M[0][2] = 3;
    M[0][3] = 4;

    M[1][0] = 2;
    M[1][1] = 3;
    M[1][2] = -2;
    M[1][3] = 5;

    M[2][0] = 1;
    M[2][1] = 2;
    M[2][2] = 3;
    M[2][3] = 4;

    M[3][0] = -2;
    M[3][1] = -3;
    M[3][2] = -1;
    M[3][3] = 0;

    M[4][0] = -5;
    M[4][1] = 1;
    M[4][2] = -2;
    M[4][3] = 9;

    printM(M, r, c);
    f(M, r, c, k, &M_out);
    printM(M_out, r, c);

    // TODO: free della memoria allocata.
    for (i = 0; i < r; i++)
    {
        free(M[i]);
        free(M_out[i]);
    }
    free(M);
    free(M_out);

    return 0;
}

void printM(int **M, int r, int c)
{
    int i, j;

    printf("Matrix:\n");
    for (i = 0; i < r; i++)
    {
        printf("\t[");
        for (j = 0; j < c - 1; j++)
        {
            printf("%d\t", M[i][j]);
        }
        printf("%d]\n", M[i][j]);
    }
}

void f(int **M, int r, int c, int k, int ***M_out)
{
    int i, j, val, i_temp, j_temp;

    // Allocaizone della memoria per la matrice di output
    (*M_out) = (int **)malloc(r * sizeof(int *));
    if ((*M_out) == NULL)
    {
        printf("Cannot allocate memory for output matrix!\n");
        exit(-1);
    }
    for (i = 0; i < r; i++)
    {
        (*M_out)[i] = (int *)malloc(c * sizeof(int));
        if ((*M_out)[i] == NULL)
        {
            printf("Cannot allocate memory for output matrix!\n");
            exit(-1);
        }
    }

    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            // itero per ogni elemento della matrice e calcolo
            // il nuovo valore per la matrice di output.
            val = 0;

            // aggiungo celle oriz. -> Scorro j
            j_temp = j - k;
            while (j_temp <= j + k)
            {
                if (j_temp >= 0 && j_temp < c)
                {
                    val += M[i][j_temp];
                }
                j_temp++;
            }

            // aggiungo celle vert. -> Scorro i
            i_temp = i - k;
            while (i_temp <= i + k)
            {
                if (i_temp >= 0 && i_temp < r)
                {
                    val += M[i_temp][j];
                }
                i_temp++;
            }

            // Rimuovo M[i][j] x2.
            val -= M[i][j];
            val -= M[i][j];

            (*M_out)[i][j] = val;
        }
    }
}