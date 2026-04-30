#include <stdio.h>
#include <stdlib.h>

void flatten(int ***M, int r, int c, int d, int ***M_out, int *r_out, int *c_out);

int main(int argc, char *argv[])
{
    int i, j;
    int r = 3, c = 3, d = 2, r_out = 0, c_out = 0;
    int ***M, **M_out;

    M = (int ***)malloc(sizeof(int **) * d * d);
    if (M == NULL)
    {
        return -1;
    }
    for (i = 0; i < (d * d); i++)
    {
        M[i] = (int **)malloc(sizeof(int *) * r);
        if (M[i] == NULL)
        {
            return -1;
        }
        for (j = 0; j < r; j++)
        {
            M[i][j] = (int *)malloc(sizeof(int) * c);
            if (M[i][j] == NULL)
            {
                return -1;
            }
        }
    }

    M[0][0][0] = 18;
    M[0][0][1] = 19;
    M[0][0][2] = 20;

    M[0][1][0] = 9;
    M[0][1][1] = 10;
    M[0][1][2] = 11;

    M[0][2][0] = 0;
    M[0][2][1] = 1;
    M[0][2][2] = 2;

    M[1][0][0] = 12;
    M[1][0][1] = 13;
    M[1][0][2] = 14;

    M[1][1][0] = 6;
    M[1][1][1] = 7;
    M[1][1][2] = 8;

    M[1][2][0] = 0;
    M[1][2][1] = 1;
    M[1][2][2] = 2;

    M[2][0][0] = 6;
    M[2][0][1] = 7;
    M[2][0][2] = 8;

    M[2][1][0] = 3;
    M[2][1][1] = 4;
    M[2][1][2] = 5;

    M[2][2][0] = 0;
    M[2][2][1] = 1;
    M[2][2][2] = 2;

    M[3][0][0] = 0;
    M[3][0][1] = 1;
    M[3][0][2] = 2;

    M[3][1][0] = 0;
    M[3][1][1] = 1;
    M[3][1][2] = 2;

    M[3][2][0] = 0;
    M[3][2][1] = 1;
    M[3][2][2] = 2;

    flatten(M, r, c, d, &M_out, &r_out, &c_out);

    // Print output
    printf("Matrix:\n");
    for (i = 0; i < r_out; i++)
    {
        printf("[");
        for (j = 0; j < c_out; j++)
        {
            printf("%d", M_out[i][j]);
            if (j < c_out - 1)
            {
                printf("\t");
            }
        }
        printf("]\n");
    }

    for (i = 0; i < (d * d); i++)
    {
        for (j = 0; j < r; j++)
        {
            free(M[i][j]);
        }
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

void flatten(int ***M, int r, int c, int d, int ***M_out, int *r_out, int *c_out)
{
    int i, j, k;

    (*r_out) = d * r;
    (*c_out) = d * c;

    // Allocazione della nuova matrice.
    (*M_out) = (int **)malloc(sizeof(int *) * (*r_out));
    if ((*M_out) == NULL)
    {
        printf("Fatal error!\n");
        return;
    }

    for (i = 0; i < (*r_out); i++)
    {
        (*M_out)[i] = (int *)malloc((*c_out) * sizeof(int));
        if ((*M_out)[i] == NULL)
        {
            printf("Fatal error!\n");
            return;
        }
    }

    for (i = 0; i < (d * d); i++)
    {
        for (j = 0; j < r; j++)
        {
            for (k = 0; k < c; k++)
            {
                (*M_out)[j + (i / d) * r][k + (i % d) * c] = M[i][j][k];
            }
        }
    }
}