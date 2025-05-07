#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Consultatii.h"

void consoleClear();
void menu();
void subMenu();

int nrConsultatii;
Consultatie consultatii[MAX_CONSULTATII];
#define MAX_LINE 256

void salveazaConsultatii() {
    FILE *f = fopen("consultatii.txt", "w");
    if (f == NULL) {
        printf("Eroare la salvarea datelor!\n");
        return;
    }
    for (int i = 0; i < nrConsultatii; i++) {
        fprintf(f, "%d;%s;%s;%s;%s\n",
                consultatii[i].id,
                consultatii[i].numePacient,
                consultatii[i].data,
                consultatii[i].ora,
                consultatii[i].motiv);
    }
    fclose(f);
}

void actualizeazaConsultatieDupaID() {
    int idCautat;
    printf("Introdu ID-ul consultatiei de actualizat: ");
    scanf("%d", &idCautat);

    int gasit = 0;
    for (int i = 0; i < nrConsultatii; i++) {
        if (consultatii[i].id == idCautat) {
            gasit = 1;
            printf("Nume pacient nou: ");
            getchar();
            fgets(consultatii[i].numePacient, sizeof(consultatii[i].numePacient), stdin);
            consultatii[i].numePacient[strcspn(consultatii[i].numePacient, "\n")] = '\0';

            printf("Data noua (zz-ll-aaaa): ");
            fgets(consultatii[i].data, sizeof(consultatii[i].data), stdin);
            consultatii[i].data[strcspn(consultatii[i].data, "\n")] = '\0';

            printf("Ora noua (hh:mm): ");
            fgets(consultatii[i].ora, sizeof(consultatii[i].ora), stdin);
            consultatii[i].ora[strcspn(consultatii[i].ora, "\n")] = '\0';

            printf("Motiv nou: ");
            fgets(consultatii[i].motiv, sizeof(consultatii[i].motiv), stdin);
            consultatii[i].motiv[strcspn(consultatii[i].motiv, "\n")] = '\0';

            salveazaConsultatii();
            printf("[SUCCES] Consultatia a fost actualizata si salvata!\n");
            break;
        }
    }

    if (!gasit) {
        printf("[INFO] Nu a fost gasita nicio consultatie cu ID-ul %d!\n", idCautat);
    }
}

void stergeConsultatieDupaID() {
    int id, found = 0;
    printf("Introduceti ID-ul consultatiei de sters: ");
    scanf("%d", &id);

    for (int i = 0; i < nrConsultatii; i++) {
        if (consultatii[i].id == id) {
            // Shift all elements to the left
            for (int j = i; j < nrConsultatii - 1; j++) {
                consultatii[j] = consultatii[j + 1];
            }
            nrConsultatii--;
            printf("Consultatia cu ID-ul %d a fost stearsa.\n", id);
            salveazaConsultatii();
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Consultatia cu ID-ul %d nu a fost gasita.\n", id);
    }
}

void vizualizeazaToateConsultatiile() {
    printf("----Lista Consultatii----\n");
    for (int i = 0; i < nrConsultatii; i++) {
        printf("%d. %s | %s %s | Motiv: %s\n",
               consultatii[i].id,
               consultatii[i].numePacient,
               consultatii[i].data,
               consultatii[i].ora,
               consultatii[i].motiv);
    }
}
void incarcaConsultatii() {
    FILE *f = fopen("consultatii.txt", "r");
    if (f == NULL) {
        printf("[INFO] Fisierul consultatii.txt nu exista inca. Se va crea la salvare.\n");
        return;
    }

    nrConsultatii = 0;
    while (fscanf(f, "%d;%49[^;];%19[^;];%9[^;];%99[^\n]\n",
                  &consultatii[nrConsultatii].id,
                  consultatii[nrConsultatii].numePacient,
                  consultatii[nrConsultatii].data,
                  consultatii[nrConsultatii].ora,
                  consultatii[nrConsultatii].motiv) == 5) {
        nrConsultatii++;
                  }
    fclose(f);
}
int isValidDate(const char *date) {
    if (strlen(date) != 10) return 0;
    return isdigit(date[0]) && isdigit(date[1]) && date[2] == '-' &&
           isdigit(date[3]) && isdigit(date[4]) && date[5] == '-' &&
           isdigit(date[6]) && isdigit(date[7]) && isdigit(date[8]) && isdigit(date[9]);
}

int isValidTime(const char *time) {
    if (strlen(time) != 5) return 0;
    return isdigit(time[0]) && isdigit(time[1]) && time[2] == ':' &&
           isdigit(time[3]) && isdigit(time[4]);
}
void adaugaConsultatieNoua() {
    if (nrConsultatii >= MAX_CONSULTATII) {
        printf("Nu se mai pot adauga consultatii!\n");
        return;
    }

    Consultatie c;
    c.id = nrConsultatii + 1;

    printf("Nume pacient: ");
    getchar();
    fgets(c.numePacient, sizeof(c.numePacient), stdin);
    c.numePacient[strcspn(c.numePacient, "\n")] = 0;
    if (strlen(c.numePacient) == 0) {
        printf("Numele pacientului nu poate fi gol!\n");
        return;
    }

    printf("Data (zz-ll-aaaa): ");
    fgets(c.data, sizeof(c.data), stdin);
    c.data[strcspn(c.data, "\n")] = 0;
    if (!isValidDate(c.data)) {
        printf("Formatul datei este invalid! (zz-ll-aaaa)\n");
        return;
    }

    printf("Ora (hh:mm): ");
    fgets(c.ora, sizeof(c.ora), stdin);
    c.ora[strcspn(c.ora, "\n")] = 0;
    if (!isValidTime(c.ora)) {
        printf("Formatul orei este invalid! (hh:mm)\n");
        return;
    }

    printf("Motiv consultatie: ");
    fgets(c.motiv, sizeof(c.motiv), stdin);
    c.motiv[strcspn(c.motiv, "\n")] = 0;
    if (strlen(c.motiv) == 0) {
        printf("Motivul nu poate fi gol!\n");
        return;
    }

    consultatii[nrConsultatii++] = c;
    salveazaConsultatii();
    printf("Consultatia a fost adaugata si salvata!\n");
}

void adaugaConsultatie()
{
    consoleClear();
    printf("----Adauga consultatie----\n");
    adaugaConsultatieNoua(); // Call the function from Consultatii.c
}

void actualizeazaConsultatie()
{
    consoleClear();
    actualizeazaConsultatieDupaID();
}

void stergeConsultatie()
{
    consoleClear();
    printf("----Sterge consultatie------\n");
    stergeConsultatieDupaID();
    printf("\nApasa Enter pentru a continua...");
    getchar(); // To consume leftover newline
    getchar(); // Wait for user input
}

void cautaOConsultatie(const char* filename, const char* searchTerm) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    char line[MAX_LINE];
    int found = 0;

    while (fgets(line, sizeof(line), file)) {
        // Duplicate line for safe tokenization
        char lineCopy[MAX_LINE];
        strcpy(lineCopy, line);

        char* id = strtok(lineCopy, ";");
        char* name = strtok(NULL, ";");
        char* date = strtok(NULL, ";");
        char* time = strtok(NULL, ";");
        char* details = strtok(NULL, "\n");

        if ((name && strstr(name, searchTerm)) || (date && strstr(date, searchTerm))) {
            printf("\nAppointment found:\n");
            printf("ID: %s\nName: %s\nDate: %s\nTime: %s\nDetails: %s\n",
                   id, name, date, time, details);
            found = 1;
        }
    }

    if (!found) {
        printf("\nNo appointment found for search term: %s\n", searchTerm);
    }

    fclose(file);
}

void cautaConsultatie()
{
    
    char searchTerm[100];
    consoleClear();
    printf("----Cauta consultatie----\n");
    printf("Enter a name or date (dd-mm-yyyy) to search: ");
    scanf("%99s", searchTerm); 

    cautaOConsultatie("consultatii.txt", searchTerm);
}

void optiuneInvalida()
{
    consoleClear();
    printf("----Optiune invalida!----\n\n");
    printf("0. Revino la meniu\n\n");
    int optiuneSelectata2;
    printf("Selecteaza o optiune: ");

    scanf("%d", &optiuneSelectata2);
    if(optiuneSelectata2 == 0)
    {
        consoleClear();
        menu();
        return;
    }
    else
    {
        optiuneInvalida();
    }
}

void consoleClear()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void subMenu(int optiuneSelectata)
{
    switch (optiuneSelectata)
    {
    case 1:
        adaugaConsultatie();
        break;
    case 2:
        actualizeazaConsultatie();
        break;
    case 3:
        stergeConsultatie();
        break;
    case 4:
        cautaConsultatie();
        break;
    case 5:
        vizualizeazaToateConsultatiile();
        break;
    default:
        optiuneInvalida();
    }

    printf("\n");
    printf("0. Paraseste submeniul\n\n");
    printf("Selecteaza o optiune: ");

    int optiuneSelectata2;
    scanf("%d", &optiuneSelectata2);
    if(optiuneSelectata2 == 0)
    {
        consoleClear();
        menu();
    }

    if(optiuneSelectata2 != 0)
    {
        optiuneInvalida();
    }
}

void menu()
{
    consoleClear();
    printf("-----------------");
    printf("\033[1;36mMENIU\033[0m");
    printf("-----------------\n");
    printf("--");
    printf("\033[1;35m1. Adauga consultatie\033[0m");
    printf("----------------\n");
    printf("--");
    printf("\033[1;33m2. Actualizeaza consultatie\033[0m");
    printf("----------\n");
    printf("--");
    printf("\033[1;31m3. Sterge consultatie\033[0m");
    printf("----------------\n");
    printf("--");
    printf("\033[1;32m4. Cauta consultatie\033[0m");
    printf("-----------------\n");
    printf("--");
    printf("\033[1;34m5. Vizualizeaza toate consultatiile\033[0m");
    printf("--\n");
    printf("---------------");
    printf("\033[1;36m0. Iesire\033[0m");
    printf("---------------\n\n");
    printf("Selecteaza o optiune: ");

    int optiuneSelectata;
    scanf("%d", &optiuneSelectata);

    if (optiuneSelectata == 0)
    {
        consoleClear();
        printf("Iesire din program...\n");
        exit(0);
    }

    subMenu(optiuneSelectata);
}

int main()
{
    incarcaConsultatii();
    menu();
    return 0;
}