#ifndef ACT_H
#define ACT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NAME 21  // 20 caratteri + '\0'

// Struttura per rappresentare una singola attività.
typedef struct {
    char nome[MAX_NAME];
    int inizio;      // tempo di inizio
    int fine;        // tempo di fine
    int costo;       // costo dell'attività
    int assigned_to; // indice della persona assegnata (per ACTbestPlan)
} Attivita;

// Struttura per rappresentare una dipendenza tra attività.
// La coppia (from, to) indica che l’attività "from" non può iniziare
// prima che termini l’attività "to".
typedef struct {
    int from; // indice dell’attività che dipende
    int to;   // indice dell’attività da cui dipende
} Dipendenza;

// ADT principale che contiene l’elenco delle attività e delle dipendenze.
typedef struct {
    Attivita *attivita;      // array di attività
    int numAttivita;         // numero di attività
    Dipendenza *dipendenze;  // array di dipendenze
    int numDipendenze;       // numero di dipendenze
} ACT;

/* Prototipi delle funzioni richieste */

// Verifica che ogni attività rispetti le dipendenze (l’attività che dipende non
// inizi prima della fine dell’attività da cui dipende).
// Ritorna 1 se la verifica è superata, 0 altrimenti.
int ACTcheckDep(ACT a);

// Stampa le sorgenti e i pozzi se il grafo delle dipendenze è un DAG,
// oppure le radici e le foglie se il grafo è una foresta di alberi radicati.
void ACTprintSrcSnk(ACT a);

// Calcola il minimo numero di persone necessarie per svolgere tutte le attività.
int ACTminPers(ACT a);

// Calcola una assegnazione ottima delle attività alle persone, in base al criterio
// di bilanciamento dei compensi. La ripartizione viene memorizzata nel campo
// "assigned_to" di ciascuna attività.
void ACTbestPlan(ACT a);

#endif // ACT_H
