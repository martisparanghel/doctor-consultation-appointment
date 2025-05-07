#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Consultatii.h"

void actualizeazaConsultatieDupaID() {
    int idCautat;
    printf("\033[1;36mIntrodu ID-ul consultatiei de actualizat: \033[0m");
    scanf("%d", &idCautat);

    int gasit = 0;
    for (int i = 0; i < nrConsultatii; i++) {
        if (consultatii[i].id == idCautat) {
            gasit = 1;
            printf("\033[1;33mNume pacient nou: \033[0m");
            getchar();
            fgets(consultatii[i].numePacient, sizeof(consultatii[i].numePacient), stdin);
            consultatii[i].numePacient[strcspn(consultatii[i].numePacient, "\n")] = '\0';

            printf("\033[1;33mData noua (zz-ll-aaaa): \033[0m");
            fgets(consultatii[i].data, sizeof(consultatii[i].data), stdin);
            consultatii[i].data[strcspn(consultatii[i].data, "\n")] = '\0';

            printf("\033[1;33mOra noua (hh:mm): \033[0m");
            fgets(consultatii[i].ora, sizeof(consultatii[i].ora), stdin);
            consultatii[i].ora[strcspn(consultatii[i].ora, "\n")] = '\0';

            printf("\033[1;33mMotiv nou: \033[0m");
            fgets(consultatii[i].motiv, sizeof(consultatii[i].motiv), stdin);
            consultatii[i].motiv[strcspn(consultatii[i].motiv, "\n")] = '\0';

            salveazaConsultatii();
            printf("\033[1;32m[SUCCES]\033[0m Consultatia a fost actualizata si salvata!\n");
            break;
        }
    }

    if (!gasit) {
        printf("\033[1;31m[INFO]\033[0m Nu a fost gasita nicio consultatie cu ID-ul %d!\n", idCautat);
    }
}
