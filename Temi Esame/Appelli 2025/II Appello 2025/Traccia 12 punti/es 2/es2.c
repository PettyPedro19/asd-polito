/**
 * II Appello 2025 - Prova di programmazione (12 punti)
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

static int sizeR(Node_t *n, int *balanced)
{
    int sl, sr;

    // Sottoalbero vuoto: 0 nodi
    if (n == NULL)
        return 0;

    sl = sizeR(n->l, balanced);
    sr = sizeR(n->r, balanced);

    // Basta una violazione per "sporcare" il flag
    if (abs(sr - sl) > 1)
        *balanced = 0;
    
    // dimensione = sx + dx + se stesso
    return sl + sr + 1;
}

int BSTisBalanced(BST b)
{
    int isBalanced = 1;

    // Gestione casi banali
    if (b == NULL || b->root == NULL)
        return 1;

    sizeR(b->root, &isBalanced);

    return isBalanced;
}
