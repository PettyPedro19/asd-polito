#include <stdio.h>
#include <stdlib.h>

void flatten(int ***m, int r, int c, int d, int ***M_out, int *r_out, int *c_out);

int main(int argc, char *argv[])
{
    int ***matTri, **M_out, r_out = 0, c_out = 0;
    int i, j, k;

    int r = 3, c = 3, d = 2;
    matTri = (int ***)malloc(d * d * sizeof(int **));
    for (k = 0; k < (d * d); k++)
    {
        matTri[k] = (int **)malloc(r * sizeof(int *));
        for (i = 0; i < r; i++)
        {
            matTri[k][i] = (int *)malloc(c * sizeof(int));
        }
    }

    matTri[0][0][0] = 18;
    matTri[0][0][1] = 19;
    matTri[0][0][2] = 20;
    matTri[0][1][0] = 9;
    matTri[0][1][1] = 10;
    matTri[0][1][2] = 11;
    matTri[0][2][0] = 0;
    matTri[0][2][1] = 1;
    matTri[0][2][2] = 2;

    matTri[1][0][0] = 12;
    matTri[1][0][1] = 13;
    matTri[1][0][2] = 14;
    matTri[1][1][0] = 6;
    matTri[1][1][1] = 7;
    matTri[1][1][2] = 8;
    matTri[1][2][0] = 0;
    matTri[1][2][1] = 1;
    matTri[1][2][2] = 2;

    matTri[2][0][0] = 6;
    matTri[2][0][1] = 7;
    matTri[2][0][2] = 8;
    matTri[2][1][0] = 3;
    matTri[2][1][1] = 4;
    matTri[2][1][2] = 5;
    matTri[2][2][0] = 0;
    matTri[2][2][1] = 1;
    matTri[2][2][2] = 2;

    matTri[3][0][0] = 0;
    matTri[3][0][1] = 1;
    matTri[3][0][2] = 2;
    matTri[3][1][0] = 0;
    matTri[3][1][1] = 1;
    matTri[3][1][2] = 2;
    matTri[3][2][0] = 0;
    matTri[3][2][1] = 1;
    matTri[3][2][2] = 2;

    /**
     *    Allocazione per 16 matrici (4 * 4)
     */
    // int r = 2, c = 2, d = 4;
    // matTri = (int ***)malloc(d * d * sizeof(int **));
    // for (k = 0; k < (d * d); k++)
    // {
    //     matTri[k] = (int **)malloc(r * sizeof(int *));
    //     for (i = 0; i < r; i++)
    //     {
    //         matTri[k][i] = (int *)malloc(c * sizeof(int));
    //         for (j = 0; j < c; j++)
    //         {
    //             // Ogni blocco contiene il proprio indice k
    //             matTri[k][i][j] = k;
    //         }
    //     }
    // }

    flatten(matTri, r, c, d, &M_out, &r_out, &c_out);

    for (i = 0; i < r_out; i++)
    {
        printf("[");
        for (j = 0; j < c_out; j++)
        {
            printf("%d\t", M_out[i][j]);
        }
        printf("]\n");
    }

    for (k = 0; i < (d * d); k++)
    {
        for (i = 0; i < r; i++)
        {
            free(matTri[k][i]);
        }
        free(matTri[k]);
    }
    free(matTri);

    for (i = 0; i < c_out; i++)
    {
        free(M_out[i]);
    }
    free(M_out);

    return 0;
}

void flatten(int ***m, int r, int c, int d, int ***M_out, int *r_out, int *c_out)
{
    int i, j, k, i_out = 0, j_out = 0, shiftR = 0, shiftC = 0;

    *r_out = d * r;
    *c_out = d * c;

    *M_out = (int **)malloc((*r_out) * sizeof(int *));
    for (i = 0; i < (*r_out); i++)
    {
        (*M_out)[i] = (int *)malloc((*c_out) * sizeof(int));
    }

    for (k = 0; k < (d * d); k++)
    {
        for (i = 0; i < r; i++)
        {
            for (j = 0; j < c; j++)
            {
                shiftR = (k / d) * r;
                shiftC = (k % d) * c;
                i_out = i + shiftR;
                j_out = j + shiftC;
                (*M_out)[i_out][j_out] = m[k][i][j];
            }
        }
    }
}