// --- nTree.h ---
#ifndef NTREE_H
#define NTREE_H

#define N 3

// Tipo opaco: l'utente sa che esiste nTREE, ma NON conosce i campi interni.
typedef struct BT *nTree;

int countIf(nTree t);

#endif

// --- nTree.c ---
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nTree.h"

// Struttura interna del nodo — NASCOSTA all'utente.
struct node
{
    char *key;
    struct node *children[N];
};

// Wrapper dell'albero — NASCOSTO all'utente.
struct nTree
{
    struct node *root;
};

/* Conta il grado (numero figli) di un nodo */
static int degree(struct node *n) {
    int count = 0;
    for (int i = 0; i < N; i++)
        if (n->children[i] != NULL)
            count++;
    return count;
}

int countIfRec(struc node *n, int parentDegree)
{
    if (n == NULL)
    {
        return 0;
    }

    int myDegree = degree(n);
    int count = 0;

    /* Radice (parentDegree == -1): conta 1 per default */
    if (parentDegree == -1)
        count = 1;
    /* Nodo interno: conta solo se grado > grado padre */
    else if (myDegree > parentDegree)
        count = 1;

    /* Visita ricorsiva di tutti i figli */
    for (int i = 0; i < N; i++)
        count += countIfRec(n->children[i], myDegree);

    return count;
}

int countIf(nTree t)
{
    // albero vuoto
    if (t == NULL)
    {
        return 0;
    }
    return countIfRec(t->root, -1);
}