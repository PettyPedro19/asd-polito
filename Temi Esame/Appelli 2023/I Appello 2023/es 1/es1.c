#include <stdio.h>
#include <stdlib.h>

void f(int **M, int r, int c, float ***M_out);
void printM(int **M, int r, int c);
void printM_out(float **M, int r, int c);

int main(int argc, char *argv[])
{
    int i, j;
    int **M, r = 3, c = 3;
    float **M_out;

    M = (int **)malloc(r * sizeof(int *));
    for (i = 0; i < r; i++)
    {
        M[i] = (int *)malloc(c * sizeof(int));
    }

    M[0][0] = 1;
    M[0][1] = 2;
    M[0][2] = 1;

    M[1][0] = 2;
    M[1][1] = 0;
    M[1][2] = 2;

    M[2][0] = 1;
    M[2][1] = 2;
    M[2][2] = 1;

    printM(M, r, c);
    f(M, r, c, &M_out);
    printM_out(M_out, r, c);

    // Free delle matrici allocate.
    for (i = 0; i < r; i++)
    {
        free(M[i]);
    }
    free(M);

    for (i = 0; i < r; i++)
    {
        free(M_out[i]);
    }
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
        for (j = 0; j < (c - 1); j++)
        {
            printf("%d ", M[i][j]);
        }
        printf("%d]\n", M[i][c - 1]);
    }
}

void printM_out(float **M, int r, int c)
{
    int i, j;

    printf("\nMatrix output:\n");
    for (i = 0; i < r; i++)
    {
        printf("\t[");
        for (j = 0; j < (c - 1); j++)
        {
            printf("%.2f ", M[i][j]);
        }
        printf("%.2f]\n", M[i][c - 1]);
    }
}

void f(int **M, int r, int c, float ***M_out)
{
    int i, j, a, b, count;
    float sum;

    // Allocazione matrice di output.
    (*M_out) = (float **)malloc(r * sizeof(float *));
    for (i = 0; i < r; i++)
    {
        (*M_out)[i] = (float *)malloc(c * sizeof(float));
    }

    // Ciclo su ogni elemento di M.
    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            sum = 0;
            count = 0;
            for (a = i - 1; a <= i + 1; a++)
            {
                for (b = j - 1; b <= j + 1; b++)
                {
                    if (a >= 0 && a < r && b >= 0 && b < c)
                    {
                        sum += M[a][b];
                        count++;
                    }
                }
            }
            (*M_out)[i][j] = (float)(sum / count);
        }
    }
}