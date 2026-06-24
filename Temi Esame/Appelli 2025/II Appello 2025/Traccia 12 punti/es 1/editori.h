#ifndef EDITORI_H
#define EDITORI_H

typedef struct
{
    char *nome;
    struct libro **libri;
    int n_libri;
} editore_t;

typedef struct editori *editori_adt;

editori_adt EditoriDup(editori_adt e);

void EditoriFree(editori_adt e);

#endif