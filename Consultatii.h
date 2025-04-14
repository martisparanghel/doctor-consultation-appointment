#ifndef CONSULTATII_H
#define CONSULTATII_H

#define MAX_CONSULTATII 100

typedef struct {
    int id;
    char numePacient[50];
    char data[20];
    char ora[10];
    char motiv[100];
} Consultatie;

// Declare extern for global variables
extern Consultatie consultatii[MAX_CONSULTATII];
extern int nrConsultatii;

// Function declarations
void incarcaConsultatii();
void salveazaConsultatii();
void adaugaConsultatieNoua();
void vizualizeazaToateConsultatiile();
void actualizeazaConsultatieDupaID();

#endif // CONSULTATII_H