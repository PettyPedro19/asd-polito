// --- bst.h ---
#ifndef BST_H
#define BST_H

typedef struct BSTnode *link;
typedef int Key;

struct BSTnode
{
    Key key;
    link p;
    link l;
    link r;
    int N;
};

typedef struct binarysearchtree *BST;

#endif

// --- bst.c ---
#include "bst.h"

struct binarysearchtree
{
    link root;
    link z;
};

link findP(link h, Key k1, Key k2, link z)
{
    while (h != z)
    {
        if (k1 < h->key && k2 < h->key)
        {
            h = h->l;
        }
        else if (k1 > h->key && k2 > h->key)
        {
            h = h->r;
        }
        else
        {
            return h;
        }
    }
    return z;
}

int dist(link commonP, Key k, link z)
{
    int dist = 0;

    while (commonP != z && commonP->key != k)
    {
        dist++;
        if (k < commonP->key)
        {
            // Scendo a sinistra.
            commonP = commonP->l;
        }
        else if (k > commonP->key)
        {
            // scendo a destra
            commonP = commonP->r;
        }
        else
        {
            break;
        }
    }

    return dist;
}

int BSTdist(BST b, Key k1, Key k2)
{
    // Le chiavi non sono contenute nel BST.
    if (BSTsearch(b, k1) == NULL || BSTsearch(b, k2) == NULL)
        return -1;

    // Ricerca parent in comune.
    link commonP = findP(b->root, k1, k2, b->z);
    // Calcolo distanza parent -> k1
    int dist1 = dist(commonP, k1, b->z);
    // Calcolo distanza parent -> k2
    int dist2 = dist(commonP, k2, b->z);
    // Sommo le distanze
    return dist1 + dist2;
}