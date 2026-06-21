/**
 * I Appello 2024 - Prova di programmazione (12 punti)
 *
 * Esercizio 3 (6 punti)
 *
 * Il modello combinatorio da adottare è quello delle
 * disposizioni semplici. Essendo l'ordine delle parole
 * importante, poichè parola1 + parola2 può non soddsifare i
 * criteri, ma parola2 + parola1 sì
 * (e.g: parole = ["sole", "ape"] -> "sole"+"ape" NO, "ape"+"sole" SI!)
 * Per quanto riguarda il pruning: non generiamo e poi scartiamo le
 * sequenze invalide, ma ad ogni passo ricorro solo sulle parole la
 * cui iniziale è della categoria opposta alla finale dell'ultima
 * parola inserita.
 *
 */

#include <stdlib.h>
#include <string.h>

// 1. Definizione degli helper
int isVowel(char c)
{
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
        c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
        return 1;
    return 0;
}

int startsWithVowel(char *s)
{
    if (isVowel(s[0]))
        return 1;
    return 0;
}

int endsWithVowel(char *s)
{
    if (isVowel(s[strlen(s) - 1]))
        return 1;
    return 0;
}

/**
 * 2. Blocco ricorsivo
 * used[]: quali parole ho già preso (ogni parola al più una volta)
 * seq[] + seqLen: sequenza di indici scelta finora, per poter ricostruire la stringa
 * curChars: caratteri accumulati
 * prevEndsVowel: categoria della finale dell'ultima parola inserita (-1 all'inizio)
 * bestSeq/bestLen/bestChars: record da battere, passati per indirizzo perché vivono nel chiamante.
 */

void solve(char **parole, int nparole, int *used, int *seq, int seqLen, int curChars,
           int prevEndsVowel, int *bestSeq, int *bestLen, int *bestChars)
{
    int j, k;

    if (curChars > *bestChars)
    {
        *bestChars = curChars;
        *bestLen = seqLen;
        for (k = 0; k < seqLen; k++)
        {
            bestSeq[k] = seq[k];
        }
    }

    for (j = 0; j < nparole; j++)
    {
        // PRUNING: scarto quelle incompatibili poiché già usate
        if (used[j])
            continue;
        // PRUNING: scarto poiché incompatibili per incompatibilità vocale-vocale
        if (prevEndsVowel != -1 && startsWithVowel(parole[j]) == prevEndsVowel)
            continue;

        used[j] = 1;
        seq[seqLen] = j;
        solve(parole, nparole, used, seq, seqLen + 1, curChars + (int)strlen(parole[j]), endsWithVowel(parole[j]), bestSeq, bestLen, bestChars);
        // Backtracking
        used[j] = 0;
    }
}

// 3. Wrapper
char *bestConcat(char **parole, int nparole)
{
    int *used, *seq, *bestSeq;
    int bestLen = 0, bestChars = 0;
    int k;

    used = (int *)calloc(nparole, sizeof(int));
    seq = (int *)malloc(nparole * sizeof(int));
    bestSeq = (int *)malloc(nparole * sizeof(int));
    if (used == NULL || seq == NULL || bestSeq == NULL)
        return NULL;

    solve(parole, nparole, used, seq, 0, 0, -1, bestSeq, &bestLen, &bestChars);

    char *result = (char *)malloc((bestChars + 1) * sizeof(char)); // +1 per '\0'
    if (result == NULL)
    {
        free(used);
        free(seq);
        free(bestSeq);
        return NULL;
    }
    result[0] = '\0';
    for (k = 0; k < bestLen; k++)
    {
        strcat(result, parole[bestSeq[k]]);
    }

    free(used);
    free(seq);
    free(bestSeq);

    return result;
}