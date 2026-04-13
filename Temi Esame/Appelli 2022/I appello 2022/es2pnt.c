#include <stdio.h>
#include <stdlib.h>

void f(int **M, int r, int c, int *r_out, int *c_out, int ***M_out);

int main(int argc, char *argv[])
{
    int nr = 3, nc = 3, i, nr_out, nc_out;

    int **M_out, **M = (int **)malloc(nr * sizeof(int *));
    for (i = 0; i < nr; i++)
    {
        M[i] = (int *)malloc(sizeof(int) * nc);
    }

    M[0][0] = 0;
    M[0][1] = 2;
    M[0][2] = 3;
    M[1][0] = 4;
    M[1][1] = 5;
    M[1][2] = 6;
    M[2][0] = 7;
    M[2][1] = 8;
    M[2][2] = 9;

    f(M, nr, nc, &nr_out, &nc_out, &M_out);

    for (i = 0; i < nr_out; i++)
    {
        printf("[");
        for (int j = 0; j < nc_out; j++)
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

void f(int **M, int r, int c, int *r_out, int *c_out, int ***M_out)
{
    int i, j, i_out = 0, j_out = 0;

    int *validRow, *validCol;

    validRow = malloc(sizeof(int) * r);
    validCol = malloc(sizeof(int) * c);

    for (i = 0; i < r; i++)
    {
        validRow[i] = 1;
    }
    for (i = 0; i < c; i++)
    {
        validCol[i] = 1;
    }

    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            if (M[i][j] == 0)
            {
                validRow[i] = 0;
                validCol[j] = 0;
            }
        }
    }

    *r_out = 0;
    *c_out = 0;
    for (i = 0; i < r; i++)
    {
        if (validRow[i] == 1)
        {
            (*r_out)++;
        }
    }
    for (i = 0; i < c; i++)
    {
        if (validCol[i] == 1)
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
            if (validRow[i] == 1 && validCol[j] == 1)
            {
                (*M_out)[i_out][j_out] = M[i][j];
                j_out++;
                if (j_out % *c_out == 0)
                {
                    j_out = 0;
                    i_out++;
                }
            }
        }
    }
}