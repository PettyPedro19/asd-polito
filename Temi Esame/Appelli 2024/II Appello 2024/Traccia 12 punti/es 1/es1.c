/**
 * II Appello 2024 - Prova di programmazione (12 punti)
 *
 * Esercizio 1 (2 punti)
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NR 100
#define NC 50

char testo[NR][NC];
char **elenco = {"ciao", "prova", "parola"};
int np = 3;

typedef struct
{
    int r;
    int c;
} pos;

typedef struct
{
    char *parola;
    int occ;
    pos *posizioni;
} Word_t;

static int isAlpha(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return 1;
    return 0;
}

void paroleTrovate(char **elenco, int np, char testo[][NC], Word_t **output, int *nOut)
{
    Word_t *tmp;
    pos *p;
    int i, j, k, r, c, start, len, occ, totFound;

    // 1. Sovralloco e inizializzo struttura dati per salvare le parole e rispettive posizioni.
    tmp = (Word_t *)malloc(np * sizeof(Word_t));
    // Check malloc
    if (tmp == NULL)
    {
        *output = NULL;
        *nOut = 0;
        return;
    }
    for (i = 0; i < np; i++)
    {
        tmp[i].parola = elenco[i];
        tmp[i].occ = 0;
        tmp[i].posizioni = NULL;
    }

    // 2. Scansiono testo e cerco le parole
    for (r = 0; r < NR; r++)
    {
        c = 0;
        while (c < NC && testo[r][c] != '\0')
        {
            if (isAlpha(testo[r][c]))
            {
                start = c;
                // Consumo la parola e la misuro
                while (c < NC && isAlpha(testo[r][c]))
                    c++;
                len = c - start;

                for (k = 0; k < np; k++)
                {
                    // Il carattere che segue la fine della parola non deve essere alfabetico
                    if ((int)strlen(elenco[k]) == len && strncmp(elenco[k], &testo[r][start], len) == 0)
                    {
                        // La parola è in elenco, salvo posizione.
                        occ = tmp[k].occ;
                        p = realloc(tmp[k].posizioni, sizeof(pos) * (occ + 1));
                        if (p == NULL)
                            return;
                        tmp[k].posizioni = p;
                        tmp[k].posizioni[occ].r = r;
                        tmp[k].posizioni[occ].c = start;
                        tmp[k].occ++;
                    }
                }
            }
            else
            {
                c++;
            }
        }
    }
    // 3. Realloc scartando le parole con 0 occorrenze
    totFound = 0;
    for (i = 0; i < np; i++)
    {
        if (tmp[i].occ > 0)
            totFound++;
    }

    *output = (Word_t *)malloc(totFound * sizeof(Word_t));
    if (*output == NULL)
    {
        for (i = 0; i < np; i++)
        {
            free(tmp[i].posizioni);
        }
        free(tmp);
        *nOut = 0;
        return;
    }

    for (i = 0, j = 0; i < np; i++)
    {
        if (tmp[i].occ > 0)
            (*output)[j++] = tmp[i];
        else
            free(tmp[i].posizioni);
    }
    *nOut = totFound;
    free(tmp);
}
