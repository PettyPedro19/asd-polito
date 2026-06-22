/**
 * II Appello 2024 - Prova di programmazione (12 punti)
 *
 * Esercizio 2 (4 punti)
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "Heap.h"

struct BinSrcTree
{
    Node_t *root;
    int size;
};

struct Heap
{
    Item *data;
    int size;
    int maxSize;
};

Node_t *buildNode(Item *node, int i, int size)
{
    // Condizione di terminazione
    if (i >= size)
        return NULL;

    // Alloco nuovo nodo del BT
    Node_t *curr = (Node_t *)malloc(sizeof(Node_t));
    if (curr == NULL)
        return NULL;

    // Ricopio contenuto e ricorro sui figli
    curr->i = node[i];
    curr->l = buildNode(node, i * 2 + 1, size);
    curr->r = buildNode(node, i * 2 + 2, size);

    return curr;
}

BT HEAPtoBT(HEAP h)
{
    BT bt = malloc(sizeof(struct BinSrcTree));
    if (bt == NULL)
        return NULL;
    bt->size = h->size;
    bt->root = buildNode(h->data, 0, h->size);

    return bt;
}

Item BTextractLast(BT bt)
{
    int pos, nbits, len, p, i, isRight;
    int *vet;
    Node_t *curr, *parent;
    Item res;

    // Posizione dell'ultima foglia e relative scelte sx/dx
    pos = bt->size;
    nbits = 0;
    p = pos;
    while (p > 0)
    {
        nbits++;
        p = p / 2;
    }
    vet = (int *)malloc(sizeof(int) * nbits);
    if (vet == NULL)
        exit;
    len = 0;
    p = pos;
    while (p > 1)
    {
        vet[len] = p % 2;
        len++;
        p = p / 2;
    }

    // Navigo il BT
    curr = bt->root;
    parent = NULL;
    isRight = 0;
    // Non considero il bit più significativo
    for (i = len - 1; i >= 0; i--)
    {
        parent = curr;
        if (vet[i] == 0)
        {
            // Scendo a sinistra
            curr = curr->l;
            isRight = 0;
        }
        else
        {
            // Scendo a destra
            curr = curr->r;
            isRight = 1;
        }
    }
    // Libero memoria allocata per il vettore delle scelte discesa in foglia
    free(vet);

    // Siamo in foglia
    res = curr->i;
    // Libero la memoria allocata per la foglia
    free(curr);

    // Siamo rimasti in radice
    if (parent == NULL)
    {
        bt->root = NULL;
    }
    else if (isRight)
    {
        parent->r = NULL;
    }
    else
    {
        parent->l = NULL;
    }
    bt->size--;

    return res;
}
