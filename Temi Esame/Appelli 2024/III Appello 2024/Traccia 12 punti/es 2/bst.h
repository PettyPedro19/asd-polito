#ifndef BST_H
#define BST_H

typedef struct node
{
    char *val;
    struct node *p;
    struct node *l;
    struct node *r;
} Node_t;

typedef struct BinSrcTree *BST;

void BSTprintDeepest(BST b);

#endif