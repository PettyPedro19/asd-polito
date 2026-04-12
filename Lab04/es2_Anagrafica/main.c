/*
 * Politecnico di Torino — 03AAXOA Algoritmi e Strutture Dati
 * Lab 04 — Esercizio 2: Anagrafica con liste
 *
 * Autore : Marco Pedron
 * Data   : 12/04/2026
 */

/* =========================================================
 * LIBRERIE
 * ========================================================= */
#include <stdio.h>
#include <stdlib.h>

/* =========================================================
 * COSTANTI E TIPI
 * ========================================================= */
#define MAX_STR_LEN 50 + 1 // 50 + 1 '\0'
#define MAX_CODE_LEN 5 + 1 // AXXXX + '\0'

typedef struct
{
    int dd;
    int mm;
    int yyyy;
} Date;

typedef struct
{
    char code[MAX_CODE_LEN];
    char name[MAX_STR_LEN];
    char surname[MAX_STR_LEN];
    Date birth;
    char street[MAX_STR_LEN];
    char city[MAX_STR_LEN];
    int cap;
} Item;

typedef struct node
{
    Item item;
    struct node *next;
} Node;

/* =========================================================
 * DICHIARAZIONI FUNZIONI
 * ========================================================= */
void printMenu();
void printItem(Item i);
void insertFromKeyboard();
void insertSorted(Node **head, Item i);
int printToFile(char fileNameOut[MAX_STR_LEN], Node **head);
int dateCmp(Date a, Date b);

/* =========================================================
 * MAIN
 * ========================================================= */
int main(int argc, char *argv[])
{
    int opt = -1;
    Node *head = NULL; // Initialize list

    while (opt != 0)
    {
        printMenu();
        if (scanf("%d", &opt) != 1)
        {
            printf("Error reading comand. Program is closing.\b");
            return -1;
        }
        if (opt > 6 || opt < 0)
        {
            printf("Comand out of range. Please select in range [1-6]\n");
        }

        switch (opt)
        {
        case 0:
            printf("\nYou selected option %d\n", opt);
            printf("Program is closing.\n.\n..\n...");
            break;
        case 1:
            printf("\nYou selected option %d\n", opt);
            insertFromKeyboard(&head);
            break;
        case 2:
            printf("\nYou selected option %d\n", opt);
            break;
        case 3:
            printf("\nYou selected option %d\n", opt);
            break;
        case 4:
            printf("\nYou selected option %d\n", opt);
            break;
        case 5:
            printf("\nYou selected option %d\n", opt);
            break;
        case 6:
            printf("\nYou selected option %d\n", opt);
            break;
        default:
            break;
        }
    }

    return 0;
}

/* =========================================================
 * IMPLEMENTAZIONI
 * ========================================================= */
void printMenu()
{
    printf("\n\t\t\t\t\t>> MENU <<\n");
    printf("1) Acquisizione ed inserimento ordinato di un nuovo elemento in lista(da tastiera)\n");
    printf("2) Acquisizione ed inserimento ordinato di nuovi elementi in lista(da file)\n");
    printf("3) Ricerca, per codice, di un elemento\n");
    printf("4) Cancellazione(con estrazione del dato) di un elemento dalla lista, previa ricerca per codice\n");
    printf("5) Cancellazione(con estrazione del dato) di tutti gli elementi con date comprese tra 2 date lette da tastiera\n");
    printf("6) Stampa della lista su file\n");
    printf("0) Esci\n");
    printf("\nIndicare scelta: [1-6]\n>>");
}

void insertFromKeyboard(Node **head)
{
    Item new;
    char digits[5];

    printf("- Insert code:\n>>A");
    scanf("%4s", digits);
    snprintf(new.code, MAX_CODE_LEN, "A%s", digits);

    printf("- Insert name:\n>>");
    scanf("%50s", new.name);

    printf("- Insert surname:\n>>");
    scanf("%50s", new.surname);

    printf("- Insert date of birth:\n  Day [dd] >>");
    scanf("%2d", &new.birth.dd);

    printf("  Month [mm] >>");
    scanf("%2d", &new.birth.mm);

    printf("  Year [yyyy] >>");
    scanf("%4d", &new.birth.yyyy);

    printf("- Insert address:\n>>");
    scanf("%50s", new.street);

    printf("- Insert city:\n>>");
    scanf("%50s", new.city);

    printf("- Insert cap [XXXXX]:\n>>");
    scanf("%5d", &new.cap);

    // TODO: check isdigit()? are there 6 digits? Perform generics checks over params

    // TODO: implement function
    printItem(new);
    insertSorted(head, new);

    printf("Item succesfully inserted\n");
}

void printItem(Item i)
{
    printf("Item:\nCode\tName\t\tSurname\t\tBirth\t\tAddress\t\tCity\t\tCap\n");
    printf("%s\t%s\t\t%s\t\t%d/%d/%d\t\t%s\t\t%s\t\t%d\n", i.code, i.name, i.surname, i.birth.dd, i.birth.mm, i.birth.yyyy, i.street, i.city, i.cap);
}

void insertSorted(Node **head, Item i)
{
    Node *newNode;

    newNode = (Node *)malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->item = i;

    // node created, now must be ordered.
    // Case 1: empty list or new item younger than the first
    if (*head == NULL || dateCmp(i.birth, (*head)->item.birth) > 0)
    {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    // case 2: find correct position
    Node *current = *head;
    while (current->next != NULL && dateCmp(current->next->item.birth, i.birth) >= 0)
    {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
}

int printToFile(char fileNameOut[MAX_STR_LEN], Node **head)
{
    FILE *fout;
    int count = 1;
    Node *current = *head;

    // TODO: check correctness of fileNameOut format "xxx.txt"

    if ((fout = fopen(fileNameOut, "w")) == NULL)
    {
        printf("Detected problem with file name of output!\nTry again.");
        return 0; // Error code, must be executed again.
    }

    while (current != NULL)
    {
        Item *it = &current->item;
        fprintf(fout, "%2d)\t%s %s %s %02d/%02d/%04d %s %s %d\n", count,
                it->code, it->name, it->surname,
                it->birth.dd, it->birth.mm, it->birth.yyyy,
                it->street, it->city, it->cap);
        count++;
        current = current->next;
    }

    fclose(fout);
    printf("Output correctly generated in file \'%s\'.\n", fileNameOut);
    return 1;
}

/* Date comparsion: return >0 if a>b, 0 if equal , <0 if a<b */
int dateCmp(Date a, Date b)
{
    if (a.yyyy != b.yyyy)
        return a.yyyy - b.yyyy;
    if (a.mm != b.mm)
        return a.mm - b.mm;
    return a.dd - b.dd;
}
