#include <stdio.h>
#include <stdlib.h>

void f(int **M, int r, int c, int ***M_out, int *r_out, int *c_out);

int main(int argc, char *argv[])
{
    int nr = 3, nc = 4, **M, **M_out, nr_out = 0, nc_out = 0;
    int i, j;

    M = (int **)malloc(nr * sizeof(int *));
    for (i = 0; i < nr; i++)
    {
        M[i] = (int *)malloc(nc * sizeof(int));
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

    f(M, nr, nc, &M_out, &nr_out, &nc_out);

    for (i = 0; i < nr_out; i++)
    {
        printf("[");
        for (j = 0; j < nc_out; j++)
        {
            printf("%d ", M_out[i][j]);
        }
        printf("]\n");
    }

    for (i = 0; i < nr; i++)
    {
        free(M[i]);
    }
    free(M);

    for (i = 0; i < nr_out; i++)
    {
        free(M_out[i]);
    }
    free(M_out);

    return 0;
}

void f(int **M, int r, int c, int ***M_out, int *r_out, int *c_out)
{
    int i, j, i_out = 0, j_out = 0;
    int *validRows, *validCols;

    validRows = (int *)malloc(r * sizeof(int));
    validCols = (int *)malloc(c * sizeof(int));

    // Initialize valid arrays
    for (i = 0; i < r; i++)
    {
        validRows[i] = 0;
    }
    for (i = 0; i < c; i++)
    {
        validCols[i] = 0;
    }

    // Scan matrix and set valid cols and rows.
    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            if (i % 2 == 0 && j % 2 == 0)
            {
                // Both indexes are even, then set to 1 validr[i] and validc[j]
                validRows[i] = 1;
                validCols[j] = 1;
            }
        }
    }

    // get r_out and c_out
    for (i = 0; i < r; i++)
    {
        if (validRows[i] == 1)
        {
            (*r_out)++;
        }
    }
    for (i = 0; i < c; i++)
    {
        if (validCols[i] == 1)
        {
            (*c_out)++;
        }
    }

    (*M_out) = (int **)malloc((*r_out) * sizeof(int *));
    for (i = 0; i < (*r_out); i++)
    {
        (*M_out)[i] = (int *)malloc((*c_out) * sizeof(int));
    }

    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            if (validRows[i] == 1 && validCols[j] == 1)
            {
                (*M_out)[i_out][j_out] = M[i][j];
                j_out++;
                if (j_out == *c_out)
                {
                    j_out = 0;
                    i_out++;
                }
            }
        }
    }

    free(validRows);
    free(validCols);
}