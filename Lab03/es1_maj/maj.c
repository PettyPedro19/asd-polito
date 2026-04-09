/*
 * Politecnico di Torino — 03AAXOA Algoritmi e Strutture Dati
 * Lab 03 — Esercizio 1: Elemento maggioritario
 *
 * Autore : Marco Pedron
 * Data   : 09/04/2026
 */

/* =========================================================
 * LIBRERIE
 * ========================================================= */
#include <stdio.h>
#include <stdlib.h>

/* =========================================================
 * COSTANTI E TIPI
 * ========================================================= */
#define N 8

/* =========================================================
 * DICHIARAZIONI FUNZIONI
 * ========================================================= */
int majority(int *a, int dim);
int majorityR(int *a, int l, int r);

/* =========================================================
 * MAIN
 * ========================================================= */

int main(int argc, char *argv[])
{
    int vet[] = {0, 1, 0, 2, 3, 4, 0, 5};

    int maj = majority(vet, N);

    if (maj != -1)
    {
        printf("L'elemento maggioritario è: %d.\n", maj);
    }
    else
    {
        printf("L'elemento maggioritario non è presente.\n");
    }

    return 0;
}

/* =========================================================
 * IMPLEMENTAZIONI
 * ========================================================= */
int majority(int *a, int dim)
{
    return majorityR(a, 0, dim - 1);
}

int majorityR(int *a, int l, int r)
{
    int countL = 0, countR = 0;

    // Termination.
    if (l == r)
    {
        return a[l];
    }

    int majL = majorityR(a, l, (l + r) / 2);
    int majR = majorityR(a, ((l + r) / 2) + 1, r);

    for (int i = l; i <= r; i++)
    {
        if (a[i] == majL)
            countL++;
        if (a[i] == majR)
            countR++;
    }

    if (countL > (r - l + 1) / 2)
    {
        return majL;
    }
    if (countR > (r - l + 1) / 2)
    {
        return majR;
    }

    return -1;
}
