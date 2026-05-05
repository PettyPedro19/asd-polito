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
    Item key;
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
    SLIST output_list = malloc(sizeof(struct LL));
    output_list->head = NULL;
    Node_t *currO = NULL;

    while (currA != NULL || currB != NULL)
    {
        // 1. Determina il nome minimo corrente
        char currentName[16];

        if (currA == NULL)
            strcpy(currentName, currB->key.name);
        else if (currB == NULL)
            strcpy(currentName, currA->key.name);
        else if (strcmp(currA->key.name, currB->key.name) <= 0)
            strcpy(currentName, currA->key.name);
        else
            strcpy(currentName, currB->key.name);

        // 2. Somma tutti i nodi di A con questo nome
        int sum = 0;
        while (currA != NULL && strcmp(currA->key.name, currentName) == 0)
        {
            sum += currA->key.val;
            currA = currA->next;
        }

        // 3. Somma tutti i nodi di B con questo nome
        while (currB != NULL && strcmp(currB->key.name, currentName) == 0)
        {
            sum += currB->key.val;
            currB = currB->next;
        }

        // 4. Inserisci un solo nodo in output
        Node_t *newNode = malloc(sizeof(Node_t));
        newNode->next = NULL;
        strcpy(newNode->key.name, currentName);
        newNode->key.val = sum;

        if (currO == NULL)
            output_list->head = newNode;
        else
            currO->next = newNode;
        currO = newNode;
    }
    return output_list;
}
