/*
 * Politecnico di Torino — 03AAXOA Algoritmi e Strutture Dati
 * Lab 01 — Esercizio 1: Valutazione di espressioni regolari
 *
 * Autore : Marco Pedron
 * Data   : 03/03/2026
 */

/* =========================================================
 * LIBRERIE
 * ========================================================= */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* =========================================================
 * COSTANTI E TIPI
 * ========================================================= */

/* =========================================================
 * DICHIARAZIONI FUNZIONI
 * ========================================================= */

/*
 * cercaRegex - scorre src e in ogni posizione tenta un match completo della regexp.
 * Ritorna puntatore alla prima occorrenza, NULL se non trovata.
 *
 * Parametri:
 *   src - puntatore alla stringa sorgente in cui cercare
 *   regexxp - puntatore all'espressione regolare da cercare
 */
char *cercaRegexp(char *src, char *regexp);
/*
 * matchQui - tenta di abbinare regexp a partire dall'inizio di src.
 * Ritorna 1 se la regexp corrisponde completamente, 0 altrimenti.
 *
 * Parametri:
 *   src - puntatore alla stringa sorgente in cui cercare
 *   regexxp - puntatore all'espressione regolare da cercare
 */
static int matchQui(char *src, char *regexp);
/*
 * matchMetacar - verifica se il carattere c soddisfa il prossimo
 * token della regexp. Imposta *consumati = numero di caratteri
 * della regexp utilizzati dal token.
 * Ritorna 1 se c soddisfa il token, 0 altrimenti.
 */
static int matchMetacar(char c, char *regexp, int *consumati);

/* =========================================================
 * MAIN
 * ========================================================= */
int main(int argc, char *argv[])
{
    char *src = "Ciao Voto", *regexp = ".oto", *risultato = NULL;

    risultato = cercaRegexp(src, regexp);

    if (risultato != NULL)
        printf("Prima occorrenza trovata: \"%s\"\n", risultato);
    else
        printf("Nessuna occorrenza trovata.\n");

    return 0;
}

/* =========================================================
 * IMPLEMENTAZIONI
 * ========================================================= */

char *cercaRegexp(char *src, char *regexp)
{
    while (*regexp != '\0')
    {
        if (matchQui(src, regexp))
            return src;
        src++;
    }

    return NULL;
}

static int matchQui(char *src, char *regexp)
{
    int consumati;

    if (*regexp == '\0')
        return 1;
    if (*src == '\0')
        return 0;

    if (matchMetacar(*src, regexp, &consumati))
        return matchQui(src + 1, regexp + consumati);

    return 0;
}

/*
 * matchMetacar - verifica se il carattere c soddisfa il prossimo
 * token della regexp. Imposta *consumati = numero di caratteri
 * della regexp utilizzati dal token.
 * Ritorna 1 se c soddisfa il token, 0 altrimenti.
 */
static int matchMetacar(char c, char *regexp, int *consumati)
{
    /* metacarattere '.' */
    if (*regexp == '.')
    {
        *consumati = 1;
        return 1;
    }

    /* metacaratteri '\a' e '\A' */
    if (*regexp == '\\')
    {
        *consumati = 2;
        if (*(regexp + 1) == 'a')
            return islower((unsigned char)c);
        if (*(regexp + 1) == 'A')
            return isupper((unsigned char)c);
        return 0;
    }

    /* classe di caratteri '[...]' */
    if (*regexp == '[')
    {
        int negate = 0;
        char *p = regexp + 1;
        if (*p == '^')
        {
            negate = 1;
            p++;
        }
        
        char *close = strchr(p, ']');
        if (close == NULL)
            return 0;

        *consumati = (int)(close - regexp) + 1;

        int trovato = 0;
        while (p < close)
        {
            if (*p == c)
            {
                trovato = 1;
                break;
            }
            p++;
        }
        return negate ? !trovato : trovato;
    }

    /* carattere letterale */
    *consumati = 1;
    return (*regexp == c);
}