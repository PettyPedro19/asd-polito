/**
 * Appello del 27/01/2022 - Prova di programmazione (12 punti)
 *
 * Esercizio 2 (4 punti)
 *
 * bt.c file
 *
 */

#include <limits.h>
#include <stdio.h>
#include "bt.h"

struct bt
{
    Node_t *root;
};

/**
 *  Strategia: visita pre-order con finestra [min, max) aperta.
 * Ogni nodo deve soddisfare: min < n->item < max.
 * Passiamo la finestra aggiornata ai sottoalberi:
 *   - sx: [min, n->item)
 *   - dx: (n->item, max]
 */
int fRec(Node_t *n, int min, int max)
{
    // Condizione di temrinazione: siamo in foglia.
    if (n == NULL)
        return 1;
    // Controllo il nodo prima di ricorrere.
    if (min >= n->item || max <= n->item)
    {
        // Non è un BST
        return 0;
    }

    return fRec(n->sx, min, n->item) && fRec(n->dx, n->item, max);
}

int f(BT t)
{
    // Il puntatore al BST non esite, non è un BST.
    if (t == NULL)
        return 0;
    // Il BST è vuoto, quindi è un BST.
    if (t->root == NULL)
        return 1;

    return fRec(t->root, INT_MIN, INT_MAX);
}
