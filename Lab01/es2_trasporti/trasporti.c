/*
 * Politecnico di Torino — 03AAXOA Algoritmi e Strutture Dati
 * Lab 01 — Esercizio 2: Azienda di trasporti
 *
 * Autore : Marco Pedron
 * Data   : 03/03/2026
 */

/* =========================================================
 * LIBRERIE
 * ========================================================= */
#include <stdlib.h>
#include <stdio.h>

/* =========================================================
 * COSTANTI E TIPI
 * ========================================================= */
#define FILENAME "corse.txt"
#define MAX_N_ROWS 1000
#define MAX_STR_LEN 30 + 1 // "abcde..." + '\0'

typedef enum
{
    r_date,
    r_partenza,
    r_capolinea,
    r_ritardo,
    r_ritardo_tot,
    r_fine
} comando_e;

typedef struct corsa
{
    char codice_tratta[MAX_STR_LEN];
    char partenza[MAX_STR_LEN];
    char destinazione[MAX_STR_LEN];
    char data[MAX_STR_LEN];
    char ora_partenza[MAX_STR_LEN];
    char ora_arrivo[MAX_STR_LEN];
    int ritardo;
}Corsa;


/* =========================================================
 * DICHIARAZIONI FUNZIONI
 * ========================================================= */
FILE *leggiFile(){

}
comando_e leggiComando();

/* =========================================================
 * MAIN
 * ========================================================= */
int main(int argc, char *argv[])
{
    FILE *fp;

    //     Si scriva un programma C in grado di rispondere alle seguenti interrogazioni:
    // 1. elencare tutte le corse partite in un certo intervallo di date
    // 2. elencare tutti le corse partite da una certa fermata
    // 3. elencare tutti le corse che fanno capolinea in una certa fermata
    // 4. elencare tutte le corse che hanno raggiunto la destinazione in ritardo in un certo intervallo di date
    // 5. elencare il ritardo complessivo accumulato dalle corse identificate da un certo codice di tratta

    return 0;
}

/* =========================================================
 * IMPLEMENTAZIONI
 * ========================================================= */
