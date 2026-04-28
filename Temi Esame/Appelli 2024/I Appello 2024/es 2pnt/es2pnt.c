#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    char name[16];
    int val;
} Item;

typedef struct node
{
    Item item;
    struct node *next;
} Node;

typedef Node *SLIST;

static Node *newNode(Item it)
{
    Node *n = (Node *)malloc(sizeof(Node));
    if (!n)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    n->item = it;
    n->next = NULL;
    return n;
}

SLIST SLISTmerge(SLIST a, SLIST b);

int main(int argc, char *argv[])
{
    return 0;
}

SLIST SLISTmerge(SLIST a, SLIST b)
{
    // Inizializzo puntatore alla nuova lista risultato.
    SLIST head = NULL;
    Node *last = NULL;
    Item res;

    while (a != NULL && b != NULL)
    {

        // comparo l'ordine lessicografico dei name degli item delle due liste.
        int cmp = strcmp(a->item.name, b->item.name);

        if (cmp < 0)
        {
            // L'item in lista b è maggiore di quello in lista a.
            // Aggrego tutti gli item di a, uguali a quello corrente.
            res = a->item;
            a = a->next;
            while (a != NULL && strcmp(a->item.name, res.name) == 0)
            {
                res.val += a->item.val;
                a = a->next;
            }
        }
        else if (cmp > 0)
        {
            // L'item in lista a è maggiore di quello in lista b
            // Aggrego tutti gli item di b, uguali a quello corrente
            res = b->item;
            b = b->next;
            while (b != NULL && strcmp(b->item.name, res.name) == 0)
            {
                res.val += b->item.val;
                b = b->next;
            }
        }
        else
        {
            // cmp == 0
            res = a->item;
            res.val = 0;

            // Aggrego nodi uguali di a
            while (a != NULL && strcmp(a->item.name, res.name) == 0)
            {
                res.val += a->item.val;
                a = a->next;
            }

            // Aggrego nodi uguali di b
            while (b != NULL && strcmp(b->item.name, res.name) == 0)
            {
                res.val += b->item.val;
                b = b->next;
            }
        }

        // aggiungo nodo.
        Node *nodo = newNode(res);
        if (last == NULL)
            head = nodo;
        else
            last->next = nodo;
        last = nodo;
    }

    // Check se una delle due SLIST è non nulla e aggiungo la rimanenza.
    SLIST rem;
    if (a != NULL)
    {
        rem = a;
    }
    else
    {
        rem = b;
    }

    while (rem != NULL)
    {
        Item res = rem->item;

        rem = rem->next;
        while (rem != NULL && strcmp(res.name, rem->item.name) == 0)
        {
            res.val += rem->item.val;
            rem = rem->next;
        }

        Node *nodo = newNode(res);
        if (last == NULL)
        {
            head = nodo;
        }
        else
        {
            last->next = nodo;
        }
        last = nodo;
    }

    return head;
}