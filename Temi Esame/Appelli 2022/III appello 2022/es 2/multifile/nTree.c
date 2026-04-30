#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nTree.h"

struct node
{
    char *key;
    struct node *children[N];
};

struct nTree
{
    struct node *root;
};

int degree(struct node *n)
{
    int count = 0, i;

    for (i = 0; i < N; i++)
    {
        if (n->children[i] != NULL)
        {
            count++;
        }
    }
    return count;
}

int countIfRec(struct node *n, int parentDegree)
{
    int i;

    // albero non contiene nodi, mi fermo.
    if (n == NULL)
    {
        return 0;
    }

    int myDegree = degree(n);
    int count = 0;

    // Radice è unico nodo con parentDeg = -1:
    // conto 1 per default.
    if (parentDegree == -1)
    {
        count = 1;
    }
    else if (myDegree > parentDegree)
    {
        count = 1;
    }

    // Visita ricorsiva su tutti i nodi figli.
    // I figli non sono necessariamente nei primi myDegree slot dell'array.
    for (i = 0; i < N; i++)
    {
        count += countIfRec(n->children[i], myDegree);
    }

    return count;
}

int countIf(nTree t)
{
    // Albero insesistente, mi fermo.
    if (t == NULL)
    {
        return 0;
    }

    return countIfRec(t->root, -1);
}
