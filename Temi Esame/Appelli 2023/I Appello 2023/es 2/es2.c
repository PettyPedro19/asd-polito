// --- naryTree.h ---
#ifndef NARYTREE_H
#define NARYTREE_H

typedef struct node
{
    int item;
    int grade;
    struct node **nodes;
} Node_t;

typedef struct naryTree *T;

int f(T t);

#endif

// --- naryTree.c ---
#include <stdio.h>
#include <stdlib.h>
#include "naryTree.h"

struct naryTree
{
    Node_t *root;
};

int fR(Node_t *n, int *gMax)
{
    int i, childLen, maxChild, length;

    // Il nodo non esiste / condizione di terminazione.
    if (n == NULL)
    {
        return 0;
    }

    // Ricorsione su ogni nodo figlio.
    maxChild = 0;
    for (i = 0; i < n->grade; i++)
    {
        childLen = fR(n->nodes[i], gMax);
        if (n->item >= 0 && childLen > maxChild)
        {
            maxChild = childLen;
        }
    }

    if (n->item < 0)
    {
        return 0;
    }

    length = 1 + maxChild;
    if (length > *gMax)
    {
        (*gMax) = length;
    }
    return length;
}

int f(T t)
{
    int gMax = 0;
    // L'albero non esiste.
    if (t == NULL || t->root == NULL)
    {
        return 0;
    }

    fR(t->root, &gMax);
    return gMax;
}
