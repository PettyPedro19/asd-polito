/*
 * Politecnico di Torino — 03AAXOA Algoritmi e Strutture Dati
 * Lab 04 — Esercizio 1: Vertex Cover
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
#define INPUT_FILE "grafo.txt"

/* =========================================================
 * DICHIARAZIONI FUNZIONI
 * ========================================================= */
int isVertexCover(int **adj, int *W, int N);
void vertexCover(int pos, int **adj, int *W, int N, int E);

/* =========================================================
 * MAIN
 * ========================================================= */
int main(int argc, char *argv[])
{
    FILE *fin;
    int n, e, i, j, v1, v2; // n -> number of vertex, e -> number of edges.
    int **adj, *w;

    if ((fin = fopen(INPUT_FILE, "r")) == NULL)
    {
        printf("Error while opening file \'%s\'.\n", INPUT_FILE);
        return -1;
    }

    // Initializing adjacence matrix, with all edges set to 0 and init of w.
    fscanf(fin, "%d %d", &n, &e);
    adj = (int **)malloc(n * sizeof(int *));
    for (i = 0; i < n; i++)
    {
        adj[i] = malloc(n * sizeof(int));
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            adj[i][j] = 0;
        }
    }

    // Read input file and set existing edges to 1.
    while (fscanf(fin, "%d %d", &v1, &v2) == 2)
    {
        // Graph is not orienteed.
        adj[v1][v2] = 1;
        adj[v2][v1] = 1;
    }

    // Init of w.
    w = malloc(n * sizeof(int)); // w = calloc(n, sizeof(int));  // zero-inizializza

    // Compute vertex cover.
    vertexCover(0, adj, w, n, e);

    // free of w and adj and closing fin.
    free(w);
    for (i = 0; i < n; i++)
    {
        free(adj[i]);
    }
    free(adj);
    fclose(fin);

    return 0;
}

/* =========================================================
 * IMPLEMENTAZIONI
 * ========================================================= */
void vertexCover(int pos, int **adj, int *W, int N, int E)
{
    if (pos == N)
    {
        if (isVertexCover(adj, W, N))
        {
            printf("(");
            for (int i = 0; i < N; i++)
            {
                if (W[i] == 1)
                {
                    printf("%d ", i);
                }
            }
            printf(")\n");
        }
        return;
    }

    W[pos] = 0;
    vertexCover(pos + 1, adj, W, N, E);
    W[pos] = 1;
    vertexCover(pos + 1, adj, W, N, E);
}

int isVertexCover(int **adj, int *W, int N)
{
    for (int u = 0; u < N; u++)
        for (int v = u + 1; v < N; v++)
            if (adj[u][v] && !W[u] && !W[v])
                return 0; // Edge (u,v) not covered
    return 1;
}
