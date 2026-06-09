/**
 * Appello del 27/01/2022 - Prova di programmazione (12 punti)
 *
 * Esercizio 2 (4 punti)
 * 
 * Header file
 *
 */

#ifndef BT_H
#define BT_H

typedef struct node
{
    int item;
    struct node *dx;
    struct node *sx;
} Node_t;

typedef struct bt *BT;

#endif