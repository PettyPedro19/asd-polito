#include <stdio.h>
#include <stdlib.h>

int f(int *v1, int *v2, int dim1, int dim2, int **v3);
void printVect(int *v, int dimV);

int main(int argc, char *argv[])
{
    int dim1 = 6, dim2 = 2, *v3;
    int v1[] = {1, 2, 2, 2, 2, 2}, v2[] = {4, 56};

    int dim3 = f(v1, v2, dim1, dim2, &v3);

    printVect(v1, dim1);
    printVect(v2, dim2);
    printVect(v3, dim3);

    // TODO: free di v3
    free(v3);
    return 0;
}

void printVect(int *v, int dimV)
{
    printf("V = {");
    for (int i = 0; i < dimV - 1; i++)
    {
        printf("%d, ", v[i]);
    }
    printf("%d}\n", v[dimV - 1]);
}

int f(int *v1, int *v2, int dim1, int dim2, int **v3)
{
    int i = 0, j = 0, dim3 = 0, prec = -1;

    // Sovrallocazione del vettore di output
    (*v3) = (int *)malloc(dim1 * sizeof(int));

    while (i < dim1)
    {
        // Elementi di v1 uguali a elementi in v2 sono saltati.
        if (v1[i] == v2[j])
        {
            i++;
        }
        else if (v1[i] > v2[j])
        {
            // Se elemento di v1 > di v2, scorro su v2 per continuare
            // a fare controllo, con attenzione a non sforare dim2.
            j++;
            if (j == dim2)
            {
                j = dim2 - 1;
            }
        }
        else if (v1[i] != prec && v1[i] != v2[j])
        {
            // Controllo che non sia già stato inserito, altrimenti salto.
            (*v3)[dim3] = v1[i];
            prec = v1[i];
            dim3++;
            i++;
        }
        else
        {
            i++;
        }
    }

    // realloc di v3
    (*v3) = (int *)realloc(*v3, dim3 * sizeof(int));

    return dim3;
}
