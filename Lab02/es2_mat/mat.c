/*
 * Politecnico di Torino — 03AAXOA Algoritmi e Strutture Dati
 * Lab 02 — Esercizio 2: Allocazione di matrici
 *
 * Autore : Marco Pedron
 * Data   : 31/03/2026
 */

/* =========================================================
 * LIBRERIE
 * ========================================================= */
#include <stdio.h>
#include <stdlib.h>

/* =========================================================
 * COSTANTI E TIPI
 * ========================================================= */

#define FILENAME "mat.txt"

/* =========================================================
 * DICHIARAZIONI FUNZIONI
 * ========================================================= */

// int **malloc2dR(...);
// void malloc2dP(int ***, ...);
// void separa(int **mat, int nr, int nc, ...);

/* =========================================================
 * MAIN
 * ========================================================= */

int main(int argc, char *argv[])
{
    FILE *fin;
    int nr, nc;

    if ((fin = fopen(FILENAME, "r")) == NULL)
    {
        printf("Error while opening file %s!\nClosing program.", FILENAME);
        return -1;
    }
    else
    {
        fscanf(fin, "%d", &nr);
        fscanf(fin, "%d", &nc);
        printf("nr = %d, nc = %d\n", nr, nc);
    }

    return 0;
}

/* =========================================================
 * IMPLEMENTAZIONI
 * ========================================================= */
