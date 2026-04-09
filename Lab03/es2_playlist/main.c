/*
 * Politecnico di Torino — 03AAXOA Algoritmi e Strutture Dati
 * Lab 03 — Esercizio 2: Playlist
 *
 * Autore : Marco Pedron
 * Data   : 09/04/2026
 */

/* =========================================================
 * LIBRERIE
 * ========================================================= */
#include <stdio.h>
#include <stdlib.h>

/* =========================================================
 * COSTANTI E TIPI
 * ========================================================= */
#define INPUT_FILE "brani3.txt"
#define MAXC 256 // 255 chars + '\0'

typedef struct
{
    char **songs;
    int numSongs;
} Friend;

/* =========================================================
 * DICHIARAZIONI FUNZIONI
 * ========================================================= */
int princ_molt(int pos, Friend *val, char **sol, int n, int cnt);

/* =========================================================
 * MAIN
 * ========================================================= */
int main(int argc, char *argv[])
{
    FILE *fin;
    int nFriends, i, j, numPlaylistCreated = 0;
    Friend *friends;

    // Open and read file.
    if ((fin = fopen(INPUT_FILE, "r")) == NULL)
    {
        printf("Error while opening file \'%s\'.\nClosing program.", INPUT_FILE);
        return -1;
    }

    fscanf(fin, "%d", &nFriends);
    friends = (Friend *)malloc(nFriends * sizeof(Friend));
    for (i = 0; i < nFriends; i++)
    {
        fscanf(fin, "%d", &friends[i].numSongs);
        friends[i].songs = (char **)malloc(friends[i].numSongs * sizeof(char *));
        for (j = 0; j < friends[i].numSongs; j++)
        {
            friends[i].songs[j] = malloc(MAXC * sizeof(char));
            fscanf(fin, "%s", friends[i].songs[j]);
        }
    }

    // for (i = 0; i < nFriends; i++)
    // {
    //     for (j = 0; j < friends[i].numSongs; j++)
    //     {
    //         printf("- %s\n", friends[i].songs[j]);
    //     }
    //     printf("\n");
    // }

    char **sol = malloc(nFriends * sizeof(char *));
    for (i = 0; i < nFriends; i++)
    {
        sol[i] = malloc(MAXC * sizeof(char));
    }

    numPlaylistCreated = princ_molt(0, friends, sol, nFriends, numPlaylistCreated);

    printf("\n\n TOT PLAYLISTS GENERATED: %d\n", numPlaylistCreated);

    // TODO: free();
    fclose(fin);
    return 0;
}

/* =========================================================
 * IMPLEMENTAZIONI
 * ========================================================= */

int princ_molt(int pos, Friend *val, char **sol, int n, int cnt)
{
    int i;

    if (pos >= n)
    {
        for (i = 0; i < n; i++)
        {
            printf("%s ", sol[i]);
        }
        printf("\n");
        return cnt + 1;
    }
    for (i = 0; i < val[pos].numSongs; i++)
    {
        sol[pos] = val[pos].songs[i];
        cnt = princ_molt(pos + 1, val, sol, n, cnt);
    }
    return cnt;
}