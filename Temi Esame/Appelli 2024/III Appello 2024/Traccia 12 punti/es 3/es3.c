/**
 * III Appello 2024 - Prova di programmazione (12 punti)
 *
 * Esercizio 3 (6 punti)
 *
 */

#include <stdlib.h>

typedef struct
{
    int r;
    int c;
} Cella;

int minPath(char **area, int N, int M, int r0, int c0, int r1, int c1)
{
    int i, j, k;
    int head = 0, tail = 0;
    int ret = -1;                       /* default: destinazione irraggiungibile */
    int nr, nc;
    Cella tmp;
    Cella *coda;
    int **dist;
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = { 0, 0, -1, 1};

    /* Coda FIFO per la BFS: al piu' N*M celle (ogni cella entra una volta sola) */
    coda = malloc(N * M * sizeof(Cella));
    if (coda == NULL)
        return -1;

    /* Matrice delle distanze */
    dist = malloc(N * sizeof(int *));
    if (dist == NULL)
    {
        free(coda);
        return -1;
    }
    for (i = 0; i < N; i++)
    {
        dist[i] = malloc(M * sizeof(int));
        for (j = 0; j < M; j++)
            dist[i][j] = -1;            /* tutte "non visitate" */
    }

    /* Partenza: marco visitata, distanza 0, accodo */
    dist[r0][c0] = 0;
    coda[tail].r = r0;
    coda[tail].c = c0;
    tail++;

    while (tail > head)
    {
        tmp = coda[head];               /* dequeue dalla testa */
        head++;

        if (tmp.r == r1 && tmp.c == c1)
        {
            ret = dist[tmp.r][tmp.c] + 1;   /* archi -> caselle */
            break;                          /* esco: free in fondo */
        }

        for (k = 0; k < 4; k++)
        {
            nr = tmp.r + dr[k];
            nc = tmp.c + dc[k];

            /* bordi PRIMA dell'accesso ad area (corto circuito di &&) */
            if (nr >= 0 && nr < N && nc >= 0 && nc < M &&
                area[nr][nc] == '0' && dist[nr][nc] == -1)
            {
                dist[nr][nc] = dist[tmp.r][tmp.c] + 1;  /* un passo oltre il padre */
                coda[tail].r = nr;                      /* enqueue + marcatura insieme */
                coda[tail].c = nc;
                tail++;
            }
        }
    }

    /* Punto di uscita unico: libero in ordine simmetrico all'allocazione */
    for (i = 0; i < N; i++)
        free(dist[i]);
    free(dist);
    free(coda);

    return ret;
}