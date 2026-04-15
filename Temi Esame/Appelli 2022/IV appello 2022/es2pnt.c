#include <stdio.h>
#include <stdlib.h>

int f(int *v1, int *v2, int dim1, int dim2, int **v_out);

int main(int argc, char *argv[])
{
    int dim1 = 3, dim2 = 1, dim3 = -1;
    int v1[] = {1, 2, 3}, v2[] = {1}, *v3;

    dim3 = f(v1, v2, dim1, dim2, &v3);

    printf("[");
    for (int i = 0; i < dim3; i++)
    {
        printf("%d\t", v3[i]);
    }
    printf("]\n");

    // free(v3);

    return 0;
}

int f(int *v1, int *v2, int dim1, int dim2, int **v_out)
{
    int i = 0, j = 0, k = 0, last = -1;

    int *out = (int *)malloc(dim1 * sizeof(int));

    while (i < dim1 && j < dim2)
    {
        if (v1[i] == v2[j])
        {
            i++;
        }
        else if (v1[i] > v2[j])
        {
            j++;
        }
        else if (v1[i] < v2[j])
        {
            if (v1[i] != last)
            {
                out[k] = v1[i];
                last = out[k];
                k++;
            }
            i++;
        }
    }
    while (i < dim1)
    {
        if (j >= dim2)
        {
            if (v1[i] != last)
            {
                out[k] = v1[i];
                last = out[k];
                k++;
            }
            i++;
        }
    }

    (*v_out) = malloc(k * sizeof(int));
    for (i = 0; i < k; i++)
    {
        (*v_out)[i] = out[i];
    }

    free(out);
    return k;
}