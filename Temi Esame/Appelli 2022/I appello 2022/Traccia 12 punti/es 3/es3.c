#include <stdio.h>

#define MAXN 20

int N;
int M[MAXN][MAXN];
int best[MAXN];
int best_val; /* min numero di gruppi trovato finora */

int canAdd(int *sol, int p, int g)
{
    int i;
    for (i = 0; i < p; i++)
    {
        if (sol[i] == g && !M[p][i])
            return 0;
    }
    return 1;
}

void disp_rip(int *sol, int pos, int n, int nGruppi)
{
    int i, g;

    if (pos >= N)
    {
        /* Conta i gruppi effettivamente usati */
        int usati = 0;
        int usato[MAXN] = {0};
        for (i = 0; i < N; i++)
        {
            usato[sol[i]] = 1;
        }
        for (i = 0; i < n; i++)
        {
            if (usato[i])
            {
                usati++;
            }
        }
        if (usati < best_val)
        {
            best_val = usati;
            for (i = 0; i < N; i++)
            {
                best[i] = sol[i];
            }
        }
        return;
    }

    for (g = 0; g < n; g++)
    {
        /* Pruning feasibility: p puo' stare nel gruppo g? */
        if (!canAdd(sol, pos, g))
            continue;

        sol[pos] = g;
        disp_rip(sol, pos + 1, n, nGruppi);
        sol[pos] = -1;
    }
}

int main(void)
{
    int i, j;
    int sol[MAXN];

    // Lettura della matrice.
    N = 4;

    M[0][0] = 1;
    M[0][1] = 1;
    M[0][2] = 0;
    M[0][3] = 1;
    
    M[1][0] = 1;
    M[1][1] = 1;
    M[1][2] = 0;
    M[1][3] = 1;

    M[2][0] = 0;
    M[2][1] = 0;
    M[2][2] = 1;
    M[2][3] = 0;

    M[3][0] = 1;
    M[3][1] = 1;
    M[3][2] = 0;
    M[3][3] = 1;

    // Inizializzazione dei valori per la soluzione.
    for (i = 0; i < N; i++)
    {
        sol[i] = -1;
    }
    best_val = N; // caso peggiore.

    /* Prova con target crescenti */
    for (i = 1; i <= N; i++)
    {
        disp_rip(sol, 0, i, i);
        if (best_val <= i)
            break; /* trovata soluzione ottima per questo target */
    }

    printf("Minimo gruppi: %d\n", best_val);
    for (i = 0; i < best_val; i++)
    {
        printf("Gruppo %d: { ", i);
        for (j = 0; j < N; j++)
        {
            if (best[j] == i)
                printf("p%d ", j);
        }
        printf("}\n");
    }

    return 0;
}