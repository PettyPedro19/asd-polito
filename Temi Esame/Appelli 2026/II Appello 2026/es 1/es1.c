// --- list.h ---
#ifndef LIST_H
#define LIST_H
#define MAXS 40

typedef struct
{
    char name[MAXS];
    float val;
} Item;

typedef char *Key;

int KEYcmp(Key k1, Key k2)
{
    return strcmp(k1, k2);
}

void ITEMprint(Item *item)
{
    printf("name: %s, val: %f\n", item->name, item->val);
}

#endif

// --- main.c ---
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Key KEYget(Item i)
{
    return i.name;
}

float ProcessItems(Item *vet, int n, Key *keys, Item *maxp)
{
    float sum = 0;
    Key max = (char *)malloc(MAXS * sizeof(char));
    if (max == NULL)
    {
        printf("Error in malloc!\n");
        return -1;
    }
    max[0] = '\0';

    (*keys) = (char *)malloc(sizeof(char));
    if ((*keys) == NULL)
    {
        printf("Error in malloc!\n");
        return -1;
    }
    (*keys)[0] = '\0';
    int i;
    maxp = (Item *)malloc(sizeof(Item));
    if (maxp == NULL)
    {
        printf("Error in malloc!\n");
        return -1;
    }

    for (i = 0; i < n; i++)
    {
        // Somma del campo val.
        sum += vet[i].val;
        // Ricerca chiave max
        if (KEYcmp(vet[i].name, *max) > 0)
        {
            strcpy(max, vet[i].name);
            (*maxp).val = vet[i].val;
            (*maxp).name = KEYget(vet[i]);
        }

        // calcolo lunghezza parola i-esima
        int l = strlen(vet[i].name);
        l += strlen((*keys));
        // Alloco lo spazio
        (*keys) = realloc((*keys), l * sizeof(char));
        // aggancio in coda
        strcpy((*keys), (*keys), vet[i].name);
    }

    return sum;
}

int main(void)
{
    Item vet[] = {{"Parigi", 2.2}, {"Roma", 2.75}, {"Londra", 8.8}, {"Berlino", 3.75}};
    Item *maxp;
    char *keys;
    float sumVal;
    int n = sizeof(vet) / sizeof(Item);

    sumVal = ProcessItems(vet, n, &keys, &maxp);

    printf("La somma dei valori e': %f\n", sumVal);
    printf("La concatenazione delle stringhe e': %s\n", keys);
    printf("Il massimo e': ");

    ITEMprint(maxp);
    free(keys);

    return 0;
}

// La somma dei valori e': 17.500000
// La concatenazione delle stringhe e': ParigiRomaLondraBerlino
// Il massimo e': name: Roma, val: 2.750000