/**
 * I Appello 2025 - Prova di programmazione (12 punti)
 *
 * Esercizio 1 (2 punti)
 *
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Sotto sequenza intesa come sequenza di elementi non contigui.
 */
int subSeq(int *a, int na, int *b, int nb)
{
    int i = 0, j = 0;

    while (i < na && j < nb)
    {
        if (a[i] == b[j])
        {
            i++;
        }
        j++;
    }

    if (i == na)
        return 1;
    return 0;
}

int main(void)
{
    int ris;
    int na = 3, nb = 6;
    int a[] = {0, 1, 2};
    int b[] = {3, 3, 0, 3, 1, 0};

    ris = subSeq(a, na, b, nb);

    if (ris)
        printf("a è contenuto in b! :D\n");
    else
        printf("a non è contenuto in b! :C\n");

    return 0;
}