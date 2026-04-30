#include <stdio.h>
#include <stdlib.h>

void f(int **M, int r, int c, int ***M_out, int *r_out, int *c_out);
void printMat(int **M, int r, int c);

int main(int argc, char *argv[])
{
    int i;
    int r = 3, c = 4, r_out = 0, c_out = 0;
    int **M, **M_out;

    M = (int **)malloc(r * sizeof(int *));
    for (i = 0; i < r; i++)
    {
        M[i] = (int *)malloc(c * sizeof(int));
    }
    M[0][0] = 1;
    M[0][1] = 2;
    M[0][2] = 3;
    M[0][3] = 4;

    M[1][0] = 5;
    M[1][1] = 6;
    M[1][2] = 7;
    M[1][3] = 8;

    M[2][0] = 9;
    M[2][1] = 0;
    M[2][2] = 1;
    M[2][3] = 2;

    printMat(M, r, c);

    f(M, r, c, &M_out, &r_out, &c_out);

    printMat(M_out, r_out, c_out);

    for (i = 0; i < r; i++)
    {
        free(M[i]);
    }
    for (i = 0; i < r_out; i++)
    {
        free(M_out[i]);
    }
    free(M);
    free(M_out);

    return 0;
}

void printMat(int **M, int r, int c)
{
    printf("Matrix:\n");
    for (int i = 0; i < r; i++)
    {
        printf("\t[");
        for (int j = 0; j < c; j++)
        {
            printf("%d", M[i][j]);
            if (j != c - 1)
            {
                printf("\t");
            }
        }
        printf("]\n");
    }
    printf("\n");
}

void f(int **M, int r, int c, int ***M_out, int *r_out, int *c_out)
{
    int i, j, i_out, j_out;

    // Calcolo dimensione matrice di output.
    (*r_out) = r / 2 + r % 2;
    (*c_out) = c / 2 + c % 2;

    // Alloco nuova matrice di output.
    (*M_out) = (int **)malloc((*r_out) * sizeof(int *));
    for (i = 0; i < (*r_out); i++)
    {
        (*M_out)[i] = (int *)malloc((*c_out) * sizeof(int));
    }

    i_out = 0;
    j_out = 0;
    // Riempo la nuova matrice.
    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            if (i % 2 == 0 && j % 2 == 0)
            {
                // Entrambi indici sono pari.
                (*M_out)[i_out][j_out] = M[i][j];
                j_out++;
                if (j_out % (*c_out) == 0)
                {
                    i_out++;
                    j_out = 0;
                    if (i_out % (*r_out) == 0)
                    {
                        break;
                    }
                }
            }
        }
    }
}