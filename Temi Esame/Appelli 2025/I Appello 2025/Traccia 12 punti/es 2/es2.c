/**
 * I Appello 2025 - Prova di programmazione (12 punti)
 *
 * Esercizio 2 (4 punti)
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

struct BinSrcTree
{
    Node_t *root;
};

static int isFull(Node_t *n)
{
    return (n->l != NULL && n->r != NULL);
}

static void findBestPath(Node_t *n, int cnt, int *bestCount, Node_t **bestLeaf)
{
    if (n == NULL)
        return;

    if (isFull(n))
        cnt++;

    if (n->l == NULL && n->r == NULL)
    {
        if (cnt > (*bestCount))
        {
            *bestCount = cnt;
            *bestLeaf = n;
        }
        return;
    }

    findBestPath(n->l, cnt, bestCount, bestLeaf);
    findBestPath(n->r, cnt, bestCount, bestLeaf);
}

static int printPath(Node_t *p)
{
    int len = 0;

    if (p == NULL)
        return 0;
    len = printPath(p->p);
    printf("%s ", p->key);
    return len + 1;
}

int BSTprintMax2(BST b)
{
    int bestCount = -1, len;
    Node_t *bestLeaf = NULL;

    // Gestione casi banali
    if (b == NULL || b->root == NULL)
        return 0;

    findBestPath(b->root, 0, &bestCount, &bestLeaf);

    // stampo il cammino
    printf("Cammino: ");
    len = printPath(bestLeaf);
    printf("\n");

    return len;
}