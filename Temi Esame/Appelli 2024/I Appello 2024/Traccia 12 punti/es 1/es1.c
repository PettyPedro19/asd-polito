/**
 * I Appello 2024 - Prova di programmazione (12 punti)
 *
 * Esercizio 1 (2 punti)
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char name[16];
    int val;
} Item;

typedef struct node
{
    Item item;
    struct node *next;
} Node_t;

struct LL
{
    Node_t *head;
};

typedef struct LL *SLIST;

SLIST SLISTmerge(SLIST a, SLIST b)
{
    Node_t *currA = a->head;
    Node_t *currB = b->head;
    // Alloco puntatore SLIST di output.
    SLIST output = malloc(sizeof(struct LL));
    if (output == NULL)
    {
        printf("Error! Can't allocate mem for output data struct!\n");
        return NULL;
    }
    output->head = NULL;
    Node_t *currO = NULL;

    while (currA != NULL || currB != NULL)
    {
        // 1. Individuo nodo corrente minore
        char currentName[16];

        if (currA == NULL)
        {
            // Lista A vuota
            strcpy(currentName, currB->item.name);
        }
        else if (currB == NULL)
        {
            // Lista B vuota
            strcpy(currentName, currA->item.name);
        }
        else if (strcmp(currA->item.name, currB->item.name) <= 0)
        {
            // Nodo A minore o uguale di B
            strcpy(currentName, currA->item.name);
        }
        else
        {
            // Nodo B minore di A
            strcpy(currentName, currB->item.name);
        }

        int sum = 0;
        // 2. Sommo tutti i nodi uguali di A
        while (currA != NULL && strcmp(currentName, currA->item.name) == 0)
        {
            sum += currA->item.val;
            currA = currA->next;
        }

        // 3. Sommo tutti i nodi uguali di B
        while (currB != NULL && strcmp(currentName, currB->item.name) == 0)
        {
            sum += currB->item.val;
            currB = currB->next;
        }

        // 4. Unisco in unico nodo di output
        Node_t *newNode = (Node_t *)malloc(sizeof(Node_t));
        if (newNode == NULL)
        {
            printf("Error! Can't allocate mem for new node!\n");
            return output;
        }

        newNode->next = NULL;
        strcpy(newNode->item.name, currentName);
        newNode->item.val = sum;

        if (currO == NULL)
        {
            output->head = newNode;
        }
        else
        {
            currO->next = newNode;
        }
        currO = newNode;
    }

    return output;
}
