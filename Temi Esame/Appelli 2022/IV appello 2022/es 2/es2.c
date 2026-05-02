// --- threeTree.h
#ifndef THREETREE_H
#define THREETREE_H

typedef struct node
{
    int item;
    struct node *s1;
    struct node *s2;
    struct node *s3;
} Node_t;

typedef struct tTree *nTree;

void countIf(nTree t, int *count1, int *count2, int *count3);

#endif

// --- threeTree.c
#include "threeTree.h"
#include <stdio.h>
#include <stdlib.h>

struct tTree
{
    Node_t *root;
};

int countIfR(Node_t *n, int *count1, int *count2, int *count3)
{
    // il nodo non esiste:
    // - il puntatore ad albero esiste ma l'albero è vuoto
    // - proveniamo da un nodo che non ha figlio.
    if (n == NULL)
    {
        return 0;
    }
    // scendo a sinistra.
    int a = countIfR(n->s1, count1, count2, count3);
    // scendo sul nodo centrale
    int b = countIfR(n->s2, count1, count2, count3);
    // scendo a destra
    int c = countIfR(n->s3, count1, count2, count3);

    int sum = a + b + c;
    switch (sum)
    {
    case 1:
        (*count1)++;
        break;
    case 2:
        (*count2)++;
        break;
    case 3:
        (*count3)++;
        break;

    default:
        break;
    }

    // Il nodo esiste, quindi ritorno sempre 1.
    return 1;
}

void countIf(nTree t, int *count1, int *count2, int *count3)
{
    // Albero vuoto, non ha senso cominciare la visita.
    if (t == NULL)
    {
        return;
    }
    // Inizializzo contatori a zero.
    (*count1) = 0;
    (*count2) = 0;
    (*count3) = 0;
    countIfR(t->root, count1, count2, count3);
}
