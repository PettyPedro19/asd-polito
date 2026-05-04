// --- doubleLinked.h ---
#ifndef DOUBLELINKED_H
#define DOUBLELINKED_H

typedef struct Node
{
    char key;
    struct Node *prev;
    struct Node *next;
} NODE;

typedef struct DL *LIST;

void f(LIST l, int k);

#endif

// --- doubleLinked.c ---
#include <stdio.h>
#include <stdlib.h>
#include "doubleLinked.h"

struct DL
{
    NODE *head;
    NODE *tail;
};

void f(LIST l, int k)
{
    int counter;
    // Lista è vuota, oppure testa/coda indefiniti.
    if (l == NULL || l->head == NULL || l->tail == NULL)
        return;

    // Valutare se mettere controllo sul valore di k
    // La lista è ordinata in senso alfabetico crescente.

    NODE *current = l->head;
    NODE *prev = NULL;
    NODE *next = current->next;
    NODE *first = current;
    while (current != NULL)
    {
        counter = 1;
        // prev??
        // Conto quanti nodi uguali di fila ci sono.
        while (current->key == next->key)
        {
            counter++;
            current = next;
            next = current->next;
        }
        if (counter >= k)
        {
            first->next = next;
            prev = next->prev;
            while (prev != first->next)
            {
                // Libero memoria dei nodi
                prev = prev->prev;
                free(prev->next);
            }
        }

        // mi sposto al prossimo
        current = next;
        first = current;
        next = current->next;
    }
}
