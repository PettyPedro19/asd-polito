#ifndef HEAP_H
#define HEAP_H

typedef struct
{
    int val;
    int priority;
} Item;

typedef struct node
{
    Item i;
    struct node *l;
    struct node *r;
} Node_t;

typedef struct BinSrcTree *BT;

typedef struct Heap *HEAP;

BT HEAPtoBT(HEAP h);

Item BTextractLast(BT bt);
#endif