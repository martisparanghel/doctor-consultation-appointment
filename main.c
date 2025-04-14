#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Consultatii.h"

void consoleClear();
void menu();
void subMenu();

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
void adaugaConsultatieNoua() {
    if (nrConsultatii >= MAX_CONSULTATII) {
        printf("Nu se mai pot adauga consultatii!\n");
        return;
    }
    Consultatie c;
    c.id = nrConsultatii + 1;
    printf("Nume pacient: "); getchar(); fgets(c.numePacient, 50, stdin);
    c.numePacient[strcspn(c.numePacient, "\n")] = 0;
    printf("Data (zz-ll-aaaa): "); fgets(c.data, 20, stdin);
    c.data[strcspn(c.data, "\n")] = 0;
    printf("Ora (hh:mm): "); fgets(c.ora, 10, stdin);
    c.ora[strcspn(c.ora, "\n")] = 0;
    printf("Motiv consultatie: "); fgets(c.motiv, 100, stdin);
    c.motiv[strcspn(c.motiv, "\n")] = 0;

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
    printf("----Sterge consultatie----\n");
}

void cautaConsultatie()
{
    consoleClear();
    printf("----Cauta consultatie----\n");
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
    printf("---------------MENIU---------------\n");
    printf("1. Adauga consultatie\n");
    printf("2. Actualizeaza consultatie\n");
    printf("3. Sterge consultatie\n");
    printf("4. Cauta consultatie\n");
    printf("5. Vizualizeaza toate consultatiile\n\n");
    printf("0. Iesire\n\n");
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