// --- BST.h ---
#ifndef BST_H
#define BST_H

typedef struct node
{
    int key;
    struct node *sx;
    struct node *dx;
} Node_t;

typedef struct Tree *BST;

Node_t **BSTlevelizedNodes(BST b, int *n);

#endif

// --- BST.c ---
#include <stdio.h>
#include <stdlib.h>
#include "BST.h"

struct Tree
{
    Node_t *root;
};

int countNodes(Node_t *n)
{
    if (n == NULL)
        return 0;
    // Visita in pre order per conteggio totale dei nodi.
    return 1 + countNodes(n->sx) + countNodes(n->dx);
}

Node_t **BSTlevelizedNodes(BST b, int *n)
{
    // Caso base: BST vuoto.
    if (b == NULL || b->root == NULL)
    {
        (*n) = 0;
        return NULL;
    }

    // Faccio visita del grafo per contare numero di nodi.
    int count = countNodes(b->root);
    (*n) = count;

    // Alloco vettore risultato.
    Node_t **pnodes = (Node_t **)malloc(count * sizeof(Node_t *));

    int head = 0, tail = 0, idx = 0;

    // Alloco coda.
    Node_t **queue = (Node_t **)malloc(count * sizeof(Node_t *));
    // enqueue della radice.
    queue[tail] = b->root;
    tail++;

    while (head < tail)
    {
        // Dequeue.
        Node_t *curr = queue[head];
        head++;
        // Salvo il risultato.
        pnodes[idx] = curr;
        idx++;

        // Enqueue dei figli, partendo da sinistra (ordine crescente).
        if (curr->sx != NULL)
        {
            queue[tail] = curr->sx;
            tail++;
        }
        if (curr->dx != NULL)
        {
            queue[tail] = curr->dx;
            tail++;
        }
    }
    free(queue);
    return pnodes;
}