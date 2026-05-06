#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NR 6
#define NC 20 // 19 + '\0'

typedef struct
{
    int r;
    int c;
} pos;

typedef struct
{
    char *parola;
    int occ;
    pos *posizioni;
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

    return 0;
}

void paroleTrovate(char testo[NR][NC], char **elenco, int np, Item **res)
{
    int p, i, j;

    // Alloco vettore output
    (*res) = (Item *)malloc(sizeof(Item) * np);
    if ((*res) == NULL)
    {
        printf("Malloc error!\n");
        return;
    }

    // Per ogni parola nell'elenco:
    for (p = 0; p < np; p++)
    {
        // 1. Inizializzo la struttura dati.
        (*res)[p].occ = 0;
        (*res)[p].parola = elenco[p];
        (*res)[p].posizioni = NULL;

        // 2. alloco spazio per memorizzare posizioni.
        // Inizio impostando 4 posizioni.
        int cap = 4;
        int npos = 0; // numero di pos attualmente salvate.
        if (((*res)[p].posizioni = malloc(sizeof(pos) * cap)) == NULL)
        {
            printf("Malloc error!\n");
            return;
        }

        // Salvo lunghezza della p-esima parola.
        int word_len = strlen(elenco[p]);

        // 3. Ciclo sul testo.
        for (i = 0; i < NR; i++)
        {
            // Salvo lunghezza della riga i-esima del testo.
            int row_len = strlen(testo[i]);
            for (j = 0; j <= row_len - word_len; j++)
            {
                // La parola del testo è quella dell'elenco?
                if (strncmp(&testo[i][j], elenco[p], word_len) != 0)
                    continue;

                // La parola è quella del testo, controllo i confini.
                if ((j > 0 && isalpha(testo[i][j - 1])) || (j < NC && isalpha(testo[i][j + word_len])))
                    continue;

                if (npos == cap)
                {
                    // Rialloco lo spazio.
                    cap *= 2;
                    (*res)[p].posizioni = realloc((*res)[p].posizioni, cap * sizeof(pos));
                }

                // Assegno le posizioni:
                (*res)[p].posizioni[npos].r = i;
                (*res)[p].posizioni[npos].c = j;
                npos++;
            }
        }
        (*res)[p].occ = npos;
    }
}