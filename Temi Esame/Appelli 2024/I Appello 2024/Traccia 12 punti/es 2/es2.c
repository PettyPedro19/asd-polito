/**
 * I Appello 2024 - Prova di programmazione (12 punti)
 *
 * Esercizio 2 (4 punti)
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "es2.h"

struct Tree
{
    Node_t *root;
};

int countNodes(Node_t *n)
{
    // Conteggio tramite visita in pre-order.
    if (n == NULL)
        return 0;
    return 1 + countNodes(n->sx) + countNodes(n->dx);
}

Node_t **BSTlevelizedNodes(BST b, int *n)
{
    // Caso base: BST vuoto
    if (b == NULL || b->root == NULL)
    {
        (*n) = 0;
        return NULL;
    }

    // 1. Conteggio dei nodi dell'albero per allocazione
    int count = countNodes(b->root);
    (*n) = count;

    // 2. Alloco una sola volta
    Node_t **output = (Node_t **)malloc(sizeof(Node_t *) * count);
    if (output == NULL)
    {
        printf("Error! Cannot allocate memory for output array!\n");
        return NULL;
    }
    // 3. Riempo con BFS (Breadth First Search)
    // - Definizione degli indici
    int head = 0, tail = 0, i = 0;
    // - Allocazione della queue
    Node_t **queue = malloc(count * sizeof(Node_t *));
    if (queue == NULL)
        return NULL;
    // - Enqueue della radice
    queue[tail] = b->root;
    tail++;
    while (head < tail)
    {
        // Dequeue
        Node_t *current = queue[head];
        head++;
        // Salvo il risultato
        output[i] = current;
        i++;
        // Enqueue dei figli, da sx a dx (ordine crescente)
        if (current->sx != NULL)
        {
            queue[tail] = current->sx;
            tail++;
        }
        if (current->dx != NULL)
        {
            queue[tail] = current->dx;
            tail++;
        }
    }
    free(queue);
    return output;
}
