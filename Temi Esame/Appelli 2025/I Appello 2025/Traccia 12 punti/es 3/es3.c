/**
 * I Appello 2025 - Esercizio 3 (6 punti)
 * checkConcat + maxConcatSeq (cammino semplice piu' lungo).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Vero se s1 puo' essere seguita da s2: esiste I in [1, min(len)-1] tale che
 * il suffisso proprio di ordine I di s1 == prefisso proprio di ordine I di s2. */
static int checkConcat(char *s1, char *s2)
{
    int len1, len2, lim, I, i, ok;

    len1 = (int)strlen(s1);
    len2 = (int)strlen(s2);
    lim = (len1 < len2) ? len1 : len2;   /* I deve essere proprio per entrambe */

    for (I = 1; I < lim; I++)
    {
        ok = 1;
        for (i = 0; i < I; i++)
        {
            /* i-esimo char del suffisso di s1 vs i-esimo char del prefisso di s2 */
            if (s1[len1 - I + i] != s2[i])
            {
                ok = 0;
                break;
            }
        }
        if (ok)
            return 1;
    }
    return 0;
}

/* Estende la sequenza che termina in 'last' (lunga 'len').
 * Aggiorna *best e salva il cammino migliore in bestSol. */
static void explore(char **S, int n, int last, int *mark,
                    int *sol, int len, int *bestSol, int *best)
{
    int j;

    if (len > *best)
    {
        *best = len;
        for (j = 0; j < len; j++)
            bestSol[j] = sol[j];
    }

    for (j = 0; j < n; j++)
    {
        if (mark[j] == 0 && checkConcat(S[last], S[j]))
        {
            mark[j] = 1;
            sol[len] = j;
            explore(S, n, j, mark, sol, len + 1, bestSol, best);
            mark[j] = 0;            /* undo simmetrico */
        }
    }
}

int maxConcatSeq(char **S, int n)
{
    int *mark, *sol, *bestSol;
    int i, best = 0;

    if (S == NULL || n <= 0)
        return 0;

    mark    = calloc(n, sizeof(int));
    sol     = malloc(n * sizeof(int));
    bestSol = malloc(n * sizeof(int));
    if (mark == NULL || sol == NULL || bestSol == NULL)
    {
        free(mark); free(sol); free(bestSol);   /* free(NULL) e' sicuro */
        return -1;
    }

    for (i = 0; i < n; i++)         /* ogni stringa puo' iniziare la sequenza */
    {
        mark[i] = 1;
        sol[0] = i;
        explore(S, n, i, mark, sol, 1, bestSol, &best);
        mark[i] = 0;
    }

    if (best > 0)
    {
        printf("Sequenza piu' lunga: ");
        for (i = 0; i < best; i++)
            printf("%s ", S[bestSol[i]]);
        printf("\n");
    }

    free(mark);
    free(sol);
    free(bestSol);
    return best;
}

int main(void)
{
    char *S[] = {"abc", "bcd", "cde", "xyz"};
    int n = 4;
    int res;

    res = maxConcatSeq(S, n);
    printf("Lunghezza massima: %d\n", res);

    return 0;
}