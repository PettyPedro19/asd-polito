// --- LIST.h ---
#ifndef LIST_H
#define LIST_H

typedef struct node
{
    int key;
    struct node *next;
} Node_t;

typedef struct LL *LIST;

void f(LIST l);

#endif

// --- LIST.c ---
#include <stdlib.h>
#include <stdio.h>
#include "LIST.h"

struct LL
{
    Node_t *head;
};

void f(LIST l)
{
    // Lista inestite / vuota. Interrompo f.
    if (l == NULL || l->head == NULL)
    {
        return;
    }

    Node_t *curr = l->head;
    Node_t *prev = NULL;
    int pos = 0;

    while (curr != NULL)
    {
        Node_t *next = curr->next;

        if (pos % 3 == 0)
        {
            // Il nodo è in posizione divisibile per 3, cancello.
            if (prev == NULL)
            {
                // Caso testa: aggiorno head
                l->head = next;
            }
            else
            {
                prev->next = next;
            }
            // LIBERO LA MEMORIA DAL NODO ATTUALE!
            free(curr)
        }
        else
        {
            prev = curr;
        }

        // Scorro lista.
        curr = next;
        pos++;
    }
}
