#include <stdio.h>
#include <stdlib.h>

void f(int **M, int r, int c, int k, int ***M_out);
void printMat(int **M, int r, int c);

int main(int argc, char *argv[])
{
    int r = 5, c = 4, k = 2, i, j;
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

    printf("Input matrix:\n");
    printMat(M, r, c);
    f(M, r, c, k, &M_out);
    printf("\nOutput matrix:\n");
    printMat(M_out, r, c);

    for (i = 0; i < r; i++)
    {
        free(M[i]);
        free(M_out[i]);
    }
    free(M);
    free(M_out);

    return 0;
}

void f(int **M, int r, int c, int k, int ***M_out)
{
    int i, j, shift;

    (*M_out) = (int **)malloc(r * sizeof(int *));
    for (i = 0; i < r; i++)
    {
        (*M_out)[i] = (int *)malloc(c * sizeof(int));
    }

    // compute new values
    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            // Initialize to 0 output mat.
            (*M_out)[i][j] = 0;
            // row right
            shift = 1;
            while (j + shift < c && shift <= k)
            {
                (*M_out)[i][j] += M[i][j + shift];
                shift++;
            }

            // row left
            shift = 1;
            while (j - shift >= 0 && shift <= k)
            {
                (*M_out)[i][j] += M[i][j - shift];
                shift++;
            }

            // col down
            shift = 1;
            while (i + shift < r && shift <= k)
            {
                (*M_out)[i][j] += M[i + shift][j];
                shift++;
            }

            // col up
            shift = 1;
            while (i - shift >= 0 && shift <= k)
            {
                (*M_out)[i][j] += M[i - shift][j];
                shift++;
            }
        }
    }
}

void printMat(int **M, int r, int c)
{
    for (int i = 0; i < r; i++)
    {
        printf("[");
        for (int j = 0; j < c; j++)
        {
            printf("%d\t", M[i][j]);
        }
        printf("]\n");
    }
}