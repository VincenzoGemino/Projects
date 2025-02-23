#ifndef ACT_H
#define ACT_H

#include <stdio.h>
#include <stdlib.h>

#define MAXC 21  // 20 caratteri + '\0'

typedef struct elAttività *ACT;

typedef struct elAttività{
    attività *act;  // vettore delle attività
    dipendenza *dip;    // vettore delle dipendenze
    int nAtt;   // numero attività
    int nDip;   // numero dipendenze
};

typedef struct {
    char nome[MAXC]; // nome attività
    int tIni;      // tempo di inizio
    int tFin;        // tempo di fine
    int costo;       // costo dell'attività
    int assegnatoA; // indice della persona assegnata (inserita per la funzione ACTbestPlan)
} Attivita;

typedef struct { //Cambio dal nome dell'attività all'indice delle attività per ottimizzazione
    int succ; // nome dell’attività che dipende
    int preced;   // nome dell’attività da cui dipende
} Dipendenza;


/* Prototipi delle funzioni richieste */

// Verifica che ogni attività rispetti le dipendenze (l’attività che dipende non inizia prima della fine dell’attività da cui dipende).
// Ritorna 1 se la verifica è superata, 0 altrimenti.
int ACTcheckDep(ACT a);

// Stampa le sorgenti e i pozzi se il grafo delle dipendenze è un DAG, oppure le radici e le foglie se il grafo è una foresta o un albero.
void ACTprintSrcSnk(ACT a);

// Calcola il minimo numero di persone necessarie per svolgere tutte le attività.
int ACTminPers(ACT a);

// Calcola una assegnazione ottima delle attività alle persone, in base al criterio di bilanciamento dei compensi. La ripartizione viene memorizzata nel campo
// "assegnatoA" di ciascuna attività.
void ACTbestPlan(ACT a);

#endif // ACT_H
