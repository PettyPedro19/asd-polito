#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char *val;
    struct node *next;
} *link;

int countCommonNodes(link h1, link h2)
{
    // 1. dichiarazioni variabili
    int count = 0;
    link p1, p2;

    for (p1 = h1, p2 = h2; p1 != NULL && p2 != NULL;)
    {
        if (p1 == p2)
        {
            // 5. Trovato nodo comune.
            count++;
            p1 = p1->next;
            p2 = p2->next;
        }
        else
        {
            // 6.
            if (strcmp(p1->val, p2->val) < 0)
            {
                p1 = p1->next;
            }
            else
            {
                p2 = p2->next;
            }
        }
    }
    // 7. Valore di ritorno.
    return count;
}