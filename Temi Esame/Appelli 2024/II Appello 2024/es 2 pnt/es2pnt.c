#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NR 6
#define NC 20

typedef struct
{
    int r;
    int c;
} Pos;

typedef struct
{
    char *parola;
    Pos *posizioni;
    int occ;

} Item;

void paroleTrovate(char testo[NR][NC], char **elenco, int np, Item **res);

int main(int argc, char *argv[])
{

    Item *risultati;

    char testo[NR][NC] = {
        "ciao mondo hello",
        "pippo paperino123",
        "alberopluto cane",
        "123gatto topolino",
        "sole luna albero",
        "xpippo gatto x"};

    char *elenco[] = {"pippo", "albero", "gatto", "sole", "hello"};
    int np = 5;

    paroleTrovate(testo, elenco, np, &risultati);

    for (int i = 0; i < np; i++)
    {
        printf("- %s:\n", risultati[i].parola);
        int occ = risultati[i].occ;
        for (int o = 0; o < occ; o++)
        {
            printf("\t%d -> Riga: %d, Colonna: %d\n", o + 1, risultati[i].posizioni[o].r, risultati[i].posizioni[o].c);
        }
    }

    return 0;
}

void paroleTrovate(char testo[NR][NC], char **elenco, int np, Item **res)
{
    int p; // indice parola in numero parole.

    (*res) = malloc(np * sizeof(Item));
    // TODO: check che la malloc restituisca un valore corretto, altrimenti exit(failure)

    for (p = 0; p < np; p++)
    {
        // Inizializzo la struttura dati
        (*res)[p].parola = elenco[p];
        (*res)[p].posizioni = NULL;
        (*res)[p].occ = 0;

        // lunghezza della parola p-esima nell'elenco
        int len = (int)strlen(elenco[p]);

        // Inizializzo a 4 posizioni nel testo, in seguito procedo con la realloc
        int cap = 4;
        (*res)[p].posizioni = (Pos *)malloc(cap * sizeof(Pos));
        // TODO: faccio check della malloc.

        int npos = 0;
        // Inizio scansione della matrice di caratteri, aka il testo.
        for (int r = 0; r < NR; r++)
        {
            // Ottengo la lunghezza della riga
            int clen = (int)strlen(testo[r]);

            // Ciclo sui caratteri della r-esima riga, andando a fermarmi quando
            // i caratteri rimanenti sono meno della parola p-esima.
            for (int c = 0; c <= clen - len; c++)
            {
                // La parola p-esima è uguale a quella del testo?
                if (strncmp(&testo[r][c], elenco[p], len) != 0)
                    continue;

                // Il carattere che precede non deve essere alfabetico
                // (a meno che siamo ad inizio riga)
                if (c > 0 && isalpha(testo[r][c - 1]))
                    continue;

                // Il carattere che segue non deve essere alfabetico
                // (a meno che siamo a fine riga)
                if (c + len < clen && isalpha(testo[r][c + len]))
                    continue;

                // Verifico se ho raggiunto il cap del vettore posizioni.
                if (npos == cap)
                {
                    // Effettuiamo realloc per un valore doppio di cap.
                    cap *= 2;
                    (*res)[p].posizioni = (Pos *)realloc((*res)[p].posizioni, cap * sizeof(Pos));
                }

                // Assegno r e c iniziali della parola.
                (*res)[p].posizioni[npos].r = r;
                (*res)[p].posizioni[npos].c = c;
                // Incremento il counter
                npos += 1;
            }
        }
        (*res)[p].occ = npos;
    }
}