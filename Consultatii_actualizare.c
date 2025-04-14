#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Consultatii.h"

//void actualizeazaConsultatieDupaID() {
//    int idCautat;
//    printf("Introdu ID-ul consultatiei de actualizat: ");
//    scanf("%d", &idCautat);
//
//    int gasit = 0;
//    for (int i = 0; i < nrConsultatii; i++) {
//        if (consultatii[i].id == idCautat) {
//            gasit = 1;
//            printf("Nume pacient nou: ");
//            getchar();
//            fgets(consultatii[i].numePacient, sizeof(consultatii[i].numePacient), stdin);
//            consultatii[i].numePacient[strcspn(consultatii[i].numePacient, "\n")] = '\0';
//
//            printf("Data noua (zz-ll-aaaa): ");
//            fgets(consultatii[i].data, sizeof(consultatii[i].data), stdin);
//            consultatii[i].data[strcspn(consultatii[i].data, "\n")] = '\0';
//
//            printf("Ora noua (hh:mm): ");
//            fgets(consultatii[i].ora, sizeof(consultatii[i].ora), stdin);
//            consultatii[i].ora[strcspn(consultatii[i].ora, "\n")] = '\0';
//
//            printf("Motiv nou: ");
//            fgets(consultatii[i].motiv, sizeof(consultatii[i].motiv), stdin);
//            consultatii[i].motiv[strcspn(consultatii[i].motiv, "\n")] = '\0';
//
//            salveazaConsultatii();
//            printf("[SUCCES] Consultatia a fost actualizata si salvata!\n");
//            break;
//        }
//    }
//
//    if (!gasit) {
//        printf("[INFO] Nu a fost gasita nicio consultatie cu ID-ul %d!\n", idCautat);
//    }
//}