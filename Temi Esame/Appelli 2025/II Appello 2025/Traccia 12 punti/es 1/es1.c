/**
 * II Appello 2025 - Prova di programmazione (12 punti)
 *
 * Esercizio 1 (2 punti)
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "editori.h"

struct editori
{
    editore_t *editori;
    int n_editori;
};

editori_adt EditoriDup(editori_adt e)
{
    int i, j, nBooks, numEditors = e->n_editori;

    // Gestione caso banale
    if (e == NULL)
        return NULL;

    editori_adt copia = (struct editori *)malloc(sizeof(struct editori));
    if (copia == NULL)
        return NULL;

    copia->n_editori = numEditors;

    copia->editori = (editore_t *)malloc(sizeof(editore_t) * numEditors);
    if (copia->editori == NULL)
    {
        free(copia);
        return NULL;
    }

    for (i = 0; i < numEditors; i++)
    {
        // 1. Copio nome editore
        copia->editori[i].nome = (char *)malloc(sizeof(char) * strlen(e->editori[i].nome + 1)); // +1 per '\0'
        strcpy(copia->editori[i].nome, e->editori[i].nome);

        // 2. Copio numero libri e libri dell'editore
        nBooks = e->editori[i].n_libri;
        copia->editori[i].n_libri = nBooks;
        copia->editori[i].libri = (struct libro **)malloc(nBooks * sizeof(struct libro *));
        for (j = 0; j < nBooks; j++)
        {
            copia->editori[i].libri[j] = e->editori[i].libri[j];
        }
    }

    return copia;
}

void EditoriFree(editori_adt e)
{
    int i;
    int numEditors = e->n_editori;

    for (i = 0; i < numEditors; i++)
    {
        free(e->editori[i].nome);
        free(e->editori[i].libri);
    }

    free(e->editori);
    free(e);
}