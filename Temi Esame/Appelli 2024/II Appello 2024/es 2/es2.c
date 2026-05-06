// --- heap.h ---
#ifndef HEAP_H
#define HEAP_H

typedef struct
{
    char val;
    int priority;
} Item;

typedef struct node
{
    Item i;
    struct node *sx;
    struct node *dx;
} Node_t;

typedef struct Tree *BT;
typedef struct heap *HEAP;

BT HEAPtoBT(HEAP h);

#endif

// --- heap.c ---
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "heap.h"

struct Tree
{
    Node_t *root;
    int size;
};

struct heap
{
    Item *data;  // Array di Item.
    int size;    // Numero di elementi presenti.
    int maxSize; // Capacità massima.
};

Node_t *buildNode(Item *data, int i, int size)
{
    if (i >= size)
        return NULL;

    Node_t *n = malloc(sizeof(Node_t));
    n->i = data[i];
    n->sx = buildNode(data, 2 * i + 1, size);
    n->dx = buildNode(data, 2 * i + 2, size);
    return n;
}

BT HEAPtoBT(HEAP h)
{
    BT bt = malloc(sizeof(struct Tree));

    bt->size = h->size;
    bt->root = buildNode(h->data, 0, h->size);

    return bt;
}

Item BTextractLast(BT bt)
{
    // Posizione 1-based dell'ultima folgia.
    int pos = bt->size;
    int nbits = ceil(log2(pos + 1));
    int *vet = malloc(nbits * sizeof(int));

    int len = 0;
    int p = pos;
    while (p > 1)
    {
        vet[len] = p % 2;
        len++;
        p = p / 2;
    }

    // Navigo il BT seguendo il percorso dei bit.
    Node_t *curr = bt->root;
    Node_t *parent = NULL;
    int isRight = 0;
    // Non considero il bit più significativo.
    for (int i = len - 1; i >= 0; i--)
    {
        parent = curr;
        // Scendo a sinistra.
        if (vet[i] == 0)
        {
            isRight = 0;
            curr = curr->sx;
        }
        else
        {
            isRight = 1;
            curr = curr->dx;
        }
    }

    // Abbiamo raggiunto la foglia.
    Item res = curr->i;
    // Libero la memoria allocata per la foglia in questione.
    free(curr);

    if (parent == NULL)
    {
        // L'albero aveva solo la radice.
        bt->root = NULL;
    }
    else if (isRight)
    {
        parent->dx = NULL;
    }
    else
    {
        parent->sx = NULL;
    }

    bt->size--;
    return res;
}
