/*
 * Politecnico di Torino — 03AAXOA Algoritmi e Strutture Dati
 * Lab 02 — Esercizio 1: Massimo Comun Divisore
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

/* =========================================================
 * DICHIARAZIONI FUNZIONI
 * ========================================================= */

int gcd(int a, int b);

/* =========================================================
 * MAIN
 * ========================================================= */

int main(int argc, char *argv[])
{
    int n1, n2, ans;

    printf("Insert operands:\nn1 >>");
    if (scanf("%d", &n1) != 1)
    {
        printf("Input error!\n");
        return -1;
    }

    printf("\nn2 >>");
    if (scanf("%d", &n2) != 1)
    {
        printf("Input error!\n");
        return -2;
    }

    ans = gcd(n1, n2);

    printf("\nThe GCD of %d and %d is %d.", n1, n2, ans);

    return 0;
}

/* =========================================================
 * IMPLEMENTAZIONI
 * ========================================================= */

int gcd(int a, int b)
{
    // Check condition of termination
    if (b == 0)
    {
        return a;
    }

    // Check order of operands.
    if (a < b)
    {
        // switch operands
        a = a + b;
        b = a - b;
        a = a - b;
    }

    if ((a % 2 == 0) && (b % 2 == 0))
    {
        return 2 * gcd(a / 2, b / 2);
    }
    else if ((a % 2 != 0) && (b % 2 == 0))
    {
        return gcd(a, b / 2);
    }
    else if ((a % 2 == 0) && (b % 2 != 0))
    {
        return gcd(a / 2, b);
    }
    else if ((a % 2 != 0) && (b % 2 != 0))
    {
        return gcd((a - b) / 2, b);
    }
    else
    {
        return -3;
    }
}