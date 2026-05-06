#include <stdio.h>
#include <stdlib.h>

int *diffVett(int *a, int na, int *b, int nb, int *nc);
void printV(int *v, int d);

int main(int argc, char *argv[])
{
    int v1[] = {1, 2, 3, 6, 8, 10};
    int v2[] = {3, 6, 7};
    int d1 = 6, d2 = 3;

    int *v3, d3 = 0;

    printf("Vettore 1 = ");
    printV(v1, d1);
    printf("Vettore 2 = ");
    printV(v2, d2);

    v3 = diffVett(v1, d1, v2, d2, &d3);

    printf("Vettore output = ");
    printV(v3, d3);

    return 0;
}

void printV(int *v, int d)
{
    printf("{");
    for (int i = 0; i < d - 1; i++)
    {
        printf("%d ", v[i]);
    }
    printf("%d}\n", v[d - 1]);
}

int *diffVett(int *a, int na, int *b, int nb, int *nc)
{
    int i = 0, j = 0, k = 0;
    // Sovralloco. Realloc prima di return.
    int *v_out = (int *)malloc(na * sizeof(int));
    if (v_out == NULL)
    {
        printf("Error in memory allocation!\n");
        return NULL;
    }

    while (i < na && j < nb)
    {
        if (a[i] == b[j])
        {
            // Elemento in a è uguale a quello in b, quindi skip.
            i++;
            j++;
        }
        else if (a[i] < b[j])
        {
            // Elemento in a è minore di quello in b.
            // Ricopio e vanzo su a.
            v_out[k] = a[i];
            k++;
            i++;
        }
        else
        {
            // Elemento in b è minore di quello in a.
            // Avanzo su b.
            j++;
        }
    }

    // Giunti alla fine di a o di b.
    // Check che in a non ci siano più elementi altrimenti ricopio
    while (i < na)
    {
        v_out[k] = a[i];
        k++;
        i++;
    }

    // realloc
    if (k != na)
    {
        v_out = realloc(v_out, k * sizeof(int));
        if (v_out == NULL)
        {
            printf("Error in memory reallocation!\n");
            return NULL;
        }
    }

    (*nc) = k;
    return v_out;
}