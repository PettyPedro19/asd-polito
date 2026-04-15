#include <stdio.h>
#include <stdlib.h>

void f(int **M, int r, int c, int ***M_out);

int main(int argc, char *argv[])
{
    int r = 3, c = 3, i, j;
    int **M, **M_out;

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

    printf("Input matrix:\n");
    for (i = 0; i < r; i++)
    {
        printf("[");
        for (j = 0; j < c; j++)
        {
            printf("%d\t", M[i][j]);
        }
        printf("]\n");
    }

    f(M, r, c, &M_out);

    printf("\n\nOutput matrix:\n");
    for (i = 0; i < r; i++)
    {
        printf("[");
        for (j = 0; j < c; j++)
        {
            printf("%d\t", M_out[i][j]);
        }
        printf("]\n");
    }

    for (i = 0; i < r; i++)
    {
        free(M[i]);
        free(M_out[i]);
    }
    free(M);
    free(M_out);

    return 0;
}

void f(int **M, int r, int c, int ***M_out)
{
    int i, j, a, b;

    (*M_out) = (int **)malloc(r * sizeof(int *));

    for (i = 0; i < r; i++)
    {
        (*M_out)[i] = (int *)malloc(c * sizeof(int));
    }

    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            (*M_out)[i][j] = 0;

            // Upper diag
            a = i;
            b = j;
            while (a >= 0 && b < c)
            {
                // Inside boundaries of matrix
                (*M_out)[i][j] += M[a][b];
                a--;
                b++;
            }

            // Lower diag
            a = i + 1;
            b = j + 1;
            while (a < r && b < c)
            {
                // Inside boundaries of matrix
                (*M_out)[i][j] += M[a][b];
                a++;
                b++;
            }
        }
    }
}