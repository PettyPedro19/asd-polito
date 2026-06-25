/**
 * IV Appello 2025 - Prova di programmazione (12 punti)
 *
 * Esercizio 1 (2 punti)
 *
 */

typedef struct node
{
    char *val;
    struct node *next;
} *link;

int countCommonNodes(link h1, link h2)
{
    // Dichiarazione delle varaibili
    link p1, p2;
    int count = 0;

    for (p1 = h1, p2 = h2; p1 != NULL ;p1 = p1->next)
    {
        if (p1->next == p2)
        {
            // Trovato nodo comune
            count++;
            p1 = p1->next;
            p2 = p2->next;
        }
        else
        {
            
        }
    }

    return count;
}