#ifndef BST_H
#define BST_H

typedef int Item;

typedef struct node
{
    Item item;
    struct node *p;
    struct node *l;
    struct node *r;
} Node_t;

typedef struct BinSrcTree *BST;

int BSTisBalanced(BST b);

#endif