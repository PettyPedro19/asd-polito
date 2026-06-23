/**
 * III Appello 2024 - Prova di programmazione (12 punti)
 *
 * Esercizio 1 (2 punti)
 *
 */

#include <stdio.h>
#include <stdlib.h>

void printV(int *vett, int dim)
{
    printf("[");
    for (int i = 0; i < (dim - 1); i++)
    {
        printf("%d ", vett[i]);
    }
    printf("%d]\n", vett[dim - 1]);
}

int *diffVett(int *a, int na, int *b, int nb, int *nc)
{
    int i, j;

    // Sovralloco: vettore output sarà al più di dim uguale a quella di a.
    int *c = malloc(na * sizeof(int));
    if (c == NULL)
        return NULL;

    i = 0;
    j = 0;
    (*nc) = 0;
    // Scorro i due vettori parallelamente e ricopio solo gli elementi non presenti in b.
    while (i < na && j < nb)
    {
        if (a[i] < b[j])
        {
            // a[i] < b[j]: salvo in c
            c[*nc] = a[i];
            (*nc)++;
            i++;
        }
        else if (a[i] == b[j])
        {
            // a[i] == b[j]: salto
            i++;
            j++;
        }
        else
        {
            // a[i] > b[j]:
            j++;
        }
    }

    // Ricopio gli eventuali elementi rimasti in a.
    while (i < na)
    {
        c[*nc] = a[i];
        (*nc)++;
        i++;
    }

    // Realloc
    if (*nc > 0)
    {
        int *tmp = (int *)realloc(c, sizeof(int) * (*nc));
        if (tmp != NULL)
            c = tmp;
    } else {
        free(c);
        c = NULL;
    }

    return c;
}

int main(int argc, char *argv[])
{
    int na = 5, nb = 3;
    int *a = malloc(na * sizeof(int));
    int *b = malloc(nb * sizeof(int));
    if (a == NULL || b == NULL)
        return -1;

    int *c, nc;

    a[0] = 3;
    a[1] = 4;
    a[2] = 5;
    a[3] = 16;
    a[4] = 18;

    b[0] = 0;
    b[1] = 1;
    b[2] = 16;

    printf("Vettore a: ");
    printV(a, na);
    printf("Vettore b: ");
    printV(b, nb);

    c = diffVett(a, na, b, nb, &nc);
    printf("Vettore diiferenza c: ");
    printV(c, nc);

    free(a);
    free(b);
    free(c);

    return 0;
}
