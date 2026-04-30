// --- BT.h ---
#ifndef BT_H
#define BT_H

/* Nodo come quasi-ADT: struct visibile ma campo interno accessibile solo
   tramite funzioni. In un quasi-ADT la struct è dichiarata nell'header.*/
typedef struct Node
{
    int val;   // Frequenza (tutti i nodi)
    char item; // Carattere (solo le foglie, '\0' per tutti i nodi interni)
    struct Node *left;
    struct Node *right;
} Node_t;

/* H come ADT di prima classe: il tipo BT è opaco (definito solo in BT.c).
   All'esterno si conosce solo il puntatore H. */
typedef struct BT *H;

/* Prototipo della funzione richiesta dall'esercizio */
char *decode(H h, char *str);

#endif

// --- BT.c ---
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "BT.h"

/* Definizione interna (opaca) dell'ADT — non visibile fuori da BT.c */
struct BT
{
    Node_t *root;
};

void decode_r(Node_t *node, Node_t *root, char *str, int str_len, char *out, int *pos, int *i)
{
    // Caso base: nodo nullo (errore nella stringa o albero malformato)
    if (node == NULL)
    {
        return;
    }

    // Caso base: siamo su una foglia → carattere trovato
    if (node->left == NULL && node->right == NULL)
    {
        out[*pos] = node->item;
        (*pos)++;
        // Reset alla radice per decodificare il prossimo carattere
        if (*i < str_len)
        {
            decode_r(root, root, str, str_len, out, pos, i);
        }
        return;
    }

    // Stringa finita ma non siamo su una foglia: errore.
    if (*i >= str_len)
    {
        return;
    }

    char bit = str[*i];
    (*i)++;
    if (bit == '0')
    {
        decode_r(node->left, root, str, str_len, out, pos, i);
    }
    if (bit == '1')
    {
        decode_r(node->right, root, str, str_len, out, pos, i);
    }
}

char *decode(H h, char *str)
{
    // Puntatore a BT è vuoto oppure BT è vuoto o str non è fornita
    // non posso fare decodifica.
    if (h == NULL || str == NULL || h->root == NULL)
        return NULL;

    int str_len = strlen(str);  // ATTENZIONE: non sarebbe da usare perché è funz. di libreria, bisognerebbe implementarla a mano con un while.

    // Nel caso peggiore, ogni char di str è un carattere.
    char *out = (char *)malloc(sizeof(char) * (str_len + 1)); // + 1 -> '\0'.
    // Check malloc andata a buon fine
    if (out == NULL)
    {
        return NULL;
    }

    int pos = 0; // prossima posizione libera in out
    int i = 0;   // indice corrente in str

    decode_r(h->root, h->root, str, str_len, out, &pos, &i);

    out[pos] = '\0';
    return out;
}

// TODO: nel chiamante della funzione decode, bisogna fare free(out);