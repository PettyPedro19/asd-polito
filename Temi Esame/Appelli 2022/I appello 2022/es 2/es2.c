// --- bt.h ---

// Definizione del nodo del BST come quasi ADT: i dettagli devono essere
// visibili a chiunque includa l'header — il client ne conosce i campi,
// anche se non dovrebbe accedervi direttamente.
typedef struct BTnode_s
{
    int key;
    struct BTnode_s *left, *right;
} BTnode;

// Definizione come ADT del Binary Tree (implementazione in bt.c)
// L'ADT di I classe (BT) espone solo il typedef nel .h;
// la struct interna sta solo nel .c proprio per nasconderla.
// Il main.c non definisce tipi — fa solo #include "bt.h" e
// usa i tipi già definiti.
typedef struct BTree_s *BT;

// --- bt.c ---
struct BTree_s
{
    BTnode *root;
};

#include <limits.h>
#include <stdio.h>

int fR(BTnode *node, int min, int max);

int f(BT t)
{
    // Se il BT è vuoto oppure non è stato inizializzato è un BST
    if (!t || !t->root)
        return 1;
    // INT_MIN e INT_MAX da <limits.h>: intervallo iniziale senza vincoli
    return fR(t->root, INT_MIN, INT_MAX);
}

int fR(BTnode *node, int min, int max)
{
    // Arrivo da un nodo foglia e quindi il puntatore al suo figlio dx/sx è null
    if (node == NULL)
        return 1;
    // La chiave del nodo non rispetta i limiti, non è un BST.
    if (node->key < min || node->key > max)
        return 0;
    // Ricorsione sui nodi aggiornando i limiti
    return (fR(node->left, min, node->key) && fR(node->right, node->key, max));
}