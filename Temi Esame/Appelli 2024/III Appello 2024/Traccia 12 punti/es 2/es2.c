/**
 * III Appello 2024 - Prova di programmazione (12 punti)
 *
 * Esercizio 2 (4 punti)
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

struct BinSrcTree
{
    Node_t *root;
};

static void findDeepest(Node_t *curr, int depth, int *maxDepth, Node_t **maxF)
{
    if (curr = NULL)
        return;
    
    if (curr->l == NULL && curr->r == NULL)
    {
        // Sono in foglia
        if (depth > *maxDepth || (depth == *maxDepth && strcmp(curr->val, (*maxF)->val) > 0))
        {
            *maxF = curr;
            *maxDepth = depth;
        }

        return;
    }

    findDeepest(curr->l, depth + 1, maxDepth, maxF);
    findDeepest(curr->r, depth + 1, maxDepth, maxF);
}

static void printToRoot(Node_t *n, Node_t *root)
{
    printf("Path: ");
    while (n != root)
    {
        printf("%s -> ", n->val);
        n = n->p;
    }
    printf("%s\n", root->val);
}

void BSTprintDeepest(BST b)
{
    int maxDepth = -1;
    Node_t *maxF;

    // L'albero non è definito o è vuoto.
    if (b == NULL || b->root == NULL)
        return;

    // Determinare la foglia a profondità massima
    findDeepest(b->root, 0, &maxDepth, &maxF);

    // Stampa a ritroso
    printToRoot(maxF, b->root);
}