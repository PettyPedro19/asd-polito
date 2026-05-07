#include <stdlib.h>
#include <stdio.h>

int subSeq(int *a, int na, int *b, int nb);
void printV(int *vet, int dim);

int main(int argc, char *argv[])
{
    int a[] = {0, 0, 1}, na = 3;
    int b[] = {1, 0, 3, 8, 4, 0, 4, 5, 6, 1, 3}, nb = 11;

    if (subSeq(a, na, b, nb))
    {
        printV(a, na);
        printf(" è sottosequenza di ");
        printV(b, nb);
    }
    else
    {
        printf("Nessuna sottosequenza trovata!\n");
    }

    return 0;
}

void printV(int *vet, int dim)
{
    printf("Vettore: [");
    for (int i = 0; i < dim - 1; i++)
    {
        printf("%d ", vet[i]);
    }
    printf("%d]", vet[dim - 1]);
}

int subSeq(int *a, int na, int *b, int nb)
{
    int i = 0, j = 0;

    while (i < nb && j < na)
    {
        if (b[i] != a[j])
        {
            i++;
            continue;
        }

        // a[j] == b[i]
        i++;
        j++;
    }

    if (j == na)
    {
        return 1;
    }

    return 0;
}