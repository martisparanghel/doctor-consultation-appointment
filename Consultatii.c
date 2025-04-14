#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Consultatii.h"

// Define global variables once here
Consultatie consultatii[MAX_CONSULTATII];
int nrConsultatii = 0;


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


//void adaugaConsultatieNoua() {
//    if (nrConsultatii >= MAX_CONSULTATII) {
//        printf("Nu se mai pot adauga consultatii!\n");
//        return;
//    }
//    Consultatie c;
//    c.id = nrConsultatii + 1;
//    printf("Nume pacient: "); getchar(); fgets(c.numePacient, 50, stdin);
//    c.numePacient[strcspn(c.numePacient, "\n")] = 0;
//    printf("Data (zz-ll-aaaa): "); fgets(c.data, 20, stdin);
//    c.data[strcspn(c.data, "\n")] = 0;
//    printf("Ora (hh:mm): "); fgets(c.ora, 10, stdin);
//    c.ora[strcspn(c.ora, "\n")] = 0;
//    printf("Motiv consultatie: "); fgets(c.motiv, 100, stdin);
//    c.motiv[strcspn(c.motiv, "\n")] = 0;
//
//    consultatii[nrConsultatii++] = c;
//    salveazaConsultatii();
//    printf("Consultatia a fost adaugata si salvata!\n");
//}