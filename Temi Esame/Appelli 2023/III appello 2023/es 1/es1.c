#include <stdlib.h>
#include <stdio.h>

void f(int **M, int r, int c, int ***M_out);
void printM(int **M, int r, int c);

int main(int argc, char *argv[])
{
    int i, j, **M, r = 3, c = 3, **M_out;

    M = (int **)malloc(r * sizeof(int *));
    for (i = 0; i < r; i++)
    {
        M[i] = (int *)malloc(c * sizeof(int));
    }

    M[0][0] = 1;
    M[0][1] = 2;
    M[0][2] = 3;

    M[1][0] = 4;
    M[1][1] = 5;
    M[1][2] = 6;

    M[2][0] = 7;
    M[2][1] = 8;
    M[2][2] = 9;

    printM(M, r, c);

    f(M, r, c, &M_out);

    printM(M_out, r, c);

    // Free delle matrice allocate.
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

    printf("\nMatrix:\n");
    for (i = 0; i < r; i++)
    {
        printf("\t[");
        for (j = 0; j < c - 1; j++)
        {
            printf("%d\t", M[i][j]);
        }
        printf("%d]\n", M[i][c - 1]);
    }
}

void f(int **M, int r, int c, int ***M_out)
{
    int i, j;

    // Allocazione memoria per matrice di output con relativi controlli.
    (*M_out) = (int **)malloc(r * sizeof(int *));
    if ((*M_out) == NULL)
    {
        printf("Error! No mem has been allocated!\n");
        return;
    }
    for (i = 0; i < r; i++)
    {
        (*M_out)[i] = (int *)malloc(c * sizeof(int));
        if ((*M_out)[i] == NULL)
        {
            printf("Error! No mem has been allocated!\n");
            return;
        }
    }

    // Ciclo su M per calcolo nuovo val.
    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            int val = 0;
            val += M[i][j];

            // Iterazioni per diag.
            int i_temp = i + 1;
            int j_temp = j + 1;
            while (i_temp < r && j_temp < c)
            {
                val += M[i_temp][j_temp];
                i_temp++;
                j_temp++;
            }
            i_temp = i - 1;
            j_temp = j + 1;
            // Iterazioni per antidiag.
            while (i_temp >= 0 && j_temp < c)
            {
                val += M[i_temp][j_temp];
                i_temp--;
                j_temp++;
            }

            // Memorizzo val nella matrice di output.
            (*M_out)[i][j] = val;
        }
    }
}