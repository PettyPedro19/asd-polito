// --- bst.h ---
#ifndef BST_H
#define BST_H

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

void BSTprintDeepest(BST b);

#endif

// --- bst.c ---
#include "bst.h"
#include <stdio.h>
#include <string.h>

struct binarysearchtree
{
    link root;
    link z;
};

void findDeepest(link x, link z, int depth, int *maxDepth, link *maxNode)
{
    // Caso base: sottoalbero vuoto.
    if (x == z)
        return;
    // x è una foglia se entrambi i figli sono sentinelle.
    if (x->l == z && x->r == z)
    {
        if ((depth > *maxDepth) || (depth == *maxDepth && strcmp(x->item, (*maxNode)->item) > 0))
        {
            *maxDepth = depth;
            *maxNode = x;
        }
        return;
    }

    // Ricorri sui figli
    findDeepest(x->l, z, depth + 1, maxDepth, maxNode);
    findDeepest(x->r, z, depth + 1, maxDepth, maxNode);
}

void printPath(link n, link z)
{
    while (n != z)
    {
        printf("%s\n", n->item);
        n = n->p;
    }
}

void BSTprintDeepest(BST b)
{
    // caso base: bst vuoto/inesistente.
    if (b == NULL || b->root == b->z)
        return;
    // funzione di ricerca
    int max_depth = -1;
    link max_node = NULL;
    findDeepest(b->root, b->z, 0, &max_depth, &max_node);

    if (max_node != NULL)
    {
        // funzione di stampa a ritroso.
        printPath(max_node, b->z);
    }
}