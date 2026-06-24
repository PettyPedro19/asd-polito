#ifndef BST_H
#define BST_H

typedef char *Item;

typedef struct node
{
    Item key;
    struct node *p;
    struct node *l;
    struct node *r;
} Node_t;

typedef struct BinSrcTree * BST;

int BSTprintMax2(BST b);

#endif