#include <stdio.h>
#include <stdlib.h>

void print_mat(int **mat, int r, int c);
void f(int **M, int r, int c, int ***M_out, int *r_out, int *c_out);

int main(int argc, char *argv[])
{
    int i, j;
    int r = 3, c = 3, r_prime = 0, c_prime = 0;
    int **M, **M_prime;

    M = (int **)malloc(r * sizeof(int *));
    for (i = 0; i < r; i++)
    {
        M[i] = (int *)malloc(c * sizeof(int));
    }

    M[0][0] = 1;
    M[0][1] = 2;
    M[0][2] = 3;

    M[1][0] = 4;
    M[1][1] = 0;
    M[1][2] = 9;

    M[2][0] = 7;
    M[2][1] = 8;
    M[2][2] = 9;

    print_mat(M, r, c);

    f(M, r, c, &M_prime, &r_prime, &c_prime);

    print_mat(M_prime, r_prime, c_prime);

    for (i = 0; i < r; i++)
    {
        free(M[i]);
        free(M_prime[i]);
    }

    free(M);
    free(M_prime);
    return 0;
}

void print_mat(int **mat, int r, int c)
{
    printf("Matrix:\n");

    for (int i = 0; i < r; i++)
    {
        printf("\t[");
        for (int j = 0; j < c; j++)
        {
            printf("%d ", mat[i][j]);
        }
        printf("]\n");
    }
    printf("\n");
}

void f(int **M, int r, int c, int ***M_out, int *r_out, int *c_out)
{
    int i, j, i_out, j_out;
    int *r_ok, *c_ok;

    // row and col vectors to mem how many rows and cols are not 0
    r_ok = (int *)malloc(r * sizeof(int));
    c_ok = (int *)malloc(c * sizeof(int));
    for (i = 0; i < r; i++)
    {
        r_ok[i] = 1;
    }
    for (i = 0; i < c; i++)
    {
        c_ok[i] = 1;
    }

    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            if (M[i][j] == 0)
            {
                r_ok[i] = 0;
                c_ok[j] = 0;
            }
        }
    }

    (*r_out) = 0;
    for (i = 0; i < r; i++)
    {
        if (r_ok[i] != 0)
            (*r_out)++;
    }
    (*c_out) = 0;
    for (i = 0; i < c; i++)
    {
        if (c_ok[i] != 0)
            (*c_out)++;
    }

    (*M_out) = (int **)malloc((*r_out) * sizeof(int *));
    for (i = 0; i < (*r_out); i++)
    {
        (*M_out)[i] = (int *)malloc((*c_out) * sizeof(int));
    }

    i_out = 0;
    j_out = 0;
    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            if (r_ok[i] && c_ok[j])
            {
                (*M_out)[i_out][j_out] = M[i][j];
                j_out++;
                if (j_out == (*c_out))
                {
                    j_out = 0;
                    i_out++;
                    if (i_out > (*c_out))
                    {
                        printf("Fatal error!\n");
                        break;
                    }
                }
            }
        }
    }
}