#ifndef ES2_H
#define ES2_H

typedef struct node
{
    int val;
    struct node *sx;
    struct node *dx;
} Node_t;

typedef struct Tree *BST;

Node_t **BSTlevelizedNodes(BST b, int *n);

#endif