/**
 * II Appello 2024 - Prova di programmazione (12 punti)
 *
 * Esercizio 3 (6 punti)
 *
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * La  funzione  deve  generare  e  stampare  tutti  i  numeri  nella  base  B
 * rappresentati  su  NC  cifre, rispettando i seguenti vincoli:
 *
 * la cifra più significativa non può essere 0;
 * al massimo una delle cifre presenti può apparire più di una volta nel numero;
 * la somma delle cifre presenti nel numero deve essere maggiore o uguale a minS.
 */

void solve(int B, int NC, int minS, int *sol, int pos, int *repsCifr, int *cntSol)
{
    int i, j, isOnly, sumCfr;

    // Siamo alla fine del vettore sol, stampa?
    if (pos >= NC)
    {
        sumCfr = 0;
        for (i = 0; i < NC; i++)
        {
            sumCfr += sol[i];
        }
        if (sumCfr >= minS)
        {
            (*cntSol)++;
            printf("%d) Numero valido: ", *cntSol);
            for (i = 0; i < NC; i++)
            {
                printf("%d ", sol[i]);
            }
            printf("\n");
        }

        return;
    }

    for (i = 0; i < B; i++)
    {
        // If pos == 0, cifra attuale non può essere 0
        if (pos == 0 && i == 0)
            continue;
        // Se cifra non ancora usata, posso usarla
        if (repsCifr[i] == 0)
        {
            sol[pos] = i;
            repsCifr[i]++;
            solve(B, NC, minS, sol, pos + 1, repsCifr, cntSol);
            // Backtrack
            repsCifr[i]--;
        }
        else
        {
            // Altrimenti se usata, devo valutare che sia l'unica ad essere ripetuta.
            isOnly = 1;
            for (j = 0; j < B; j++)
            {
                if (j != i && repsCifr[j] > 1)
                    isOnly = 0;
            }

            if (isOnly)
            {
                sol[pos] = i;
                repsCifr[i]++;
                solve(B, NC, minS, sol, pos + 1, repsCifr, cntSol);
                // backtrack
                repsCifr[i]--;
            }
            else
            {
                continue;
            }
        }
    }
}

void generaNumeri(int B, int NC, int minS)
{
    /** Nella generazione dei numeri:
     * L'ordine conta -> Permutazioni/Disposizioni
     * k==n? No -> Disposizioni
     * Le cifre si possono ripetere? Sì -> Disposizioni con ripetizioni
     */
    int count = 0;
    int *sol = calloc(NC, sizeof(int));
    int *repsCifr = calloc(B, sizeof(int));
    if (sol == NULL || repsCifr == NULL)
    {
        printf("Error! Cannot allocate memory!\n");
        return;
    }
    
    solve(B, NC, minS, sol, 0, repsCifr, &count);
    free(sol);
    free(repsCifr);
}

int main(void)
{
    int base = 2, numCifr = 3, minS = 2;

    generaNumeri(base, numCifr, minS);

    return 0;
}