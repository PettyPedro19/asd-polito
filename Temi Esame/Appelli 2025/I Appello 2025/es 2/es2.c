// --- bst.h ---
#ifndef BST_H
#define BST_H
#include <string.h>

typedef char *Item;

typedef struct BSTnode *link;

struct BSTnode
{
    Item item;
    link p;
    link l;
    link r;
    int N;
};

typedef struct binarysearchtree *BST;

int BSTprintMax2(BST b);

#endif

// --- bst.c ---
#include "bst.h"
#include <stdio.h>

struct binarysearchtree
{
    link root;
    link z;
};

void findMax(link h, link z, int count, int *max, link *nodoMax)
{
    if (h == z)
        return;

    // Sono arrivato in foglia.
    if (h->l == z && h->r == z)
    {
        if ((count > *max) || (count == *max && strcmp(h->item, (*nodoMax)->item) > 0))
        {
            *max = count;
            *nodoMax = h;
        }
        return;
    }

    int haDueFigli = 0;
    if (h->l != z && h->r != z)
    {
        int haDueFigli = 1;
    }

    findMax(h->l, z, count + haDueFigli, max, nodoMax);
    findMax(h->r, z, count + haDueFigli, max, nodoMax);
}

int printMax(link n, link z)
{
    int count = 0;

    while (n != z)
    {
        printf("%s\n", n->item);
        n = n->p;
        count++;
    }

    return count;
}

int BSTprintMax2(BST b)
{
    // caso base: ritorno 0;
    if (b == NULL || b->root == b->z)
        return 0;

    int max = -1;
    link *n = NULL;
    // Determino foglia max.
    findMax(b->root, b->z, 0, &max, &n);

    // Stampo cammino e ritorno lunghezza.
    return printMax(n, b->z);
}
