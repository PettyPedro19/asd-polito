// --- bst2.h ---
#ifndef BST2_H
#define BST2_H
#include <string.h>

#define MAXC 40

typedef struct
{
    char name[MAXC];
} Item;

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

BST BSTdup(BST b);

#endif

// --- bst.c ---
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "bst2.h"

struct binarysearchtree
{
    link root;
    link z;
};

link BSTdupR(link h, link parentNew, link zOld, link zNew)
{
    if (h == zOld)
        return zNew;

    link x = malloc(sizeof(*x));
    h2->l = h1->l;
    h2->r = h1->r;
    h2->p = h1->p;
    h2->N = h1->N;
    strcpy(h2->item, h1->item);
    BSTdupR(h1->l, h2->l, z);
    BSTdupR(h1->r, h2->r, z);
}

BST BSTdup(BST b)
{
    // BST inesistente.
    if (b == NULL)
        return NULL;

    // BST non vuoto, inizializzo res ad albero vuoto.
    BST res = BSTinit();

    // BST non ha nodi, ritorno albero vuoto.
    if (b->root == b->z)
        return res;
        

    // Faccio visita in order per ricostruire il BST.
    res->root = BSTdupR(b->root, res->z, b->z, res->z);

    return res;
}


// Funzione ricorsiva: alloca un nuovo nodo, copia i dati, ricorre sui figli
link dupR(link h, link parentNew, link zOld, link zNew)
{
    if (h == zOld)
        return zNew;                  // caso base: foglia sentinella

    link x = malloc(sizeof *x);      // alloca nuovo nodo
    if (x == NULL) return zNew;

    x->item = h->item;               // copia la struct (struct assignment)
    x->N    = h->N;
    x->p    = parentNew;             // parent = il nuovo nodo padre

    // ricorre: i figli del nuovo nodo sono nuovi nodi
    x->l = dupR(h->l, x, zOld, zNew);
    x->r = dupR(h->r, x, zOld, zNew);

    return x;
}
