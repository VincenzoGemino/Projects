#include "act.h"
#include <string.h>

/* ---------------- Funzioni di supporto ---------------- */

// Funzione per confrontare gli eventi: in caso di tempo uguale, l’evento di fine (-1)
// precede quello di inizio (+1).
typedef struct {
    int time;
    int type; // +1: inizio, -1: fine
} Event;

static int cmpEvent(const void *p1, const void *p2) {
    const Event *e1 = (const Event *)p1;
    const Event *e2 = (const Event *)p2;
    if (e1->time == e2->time)
        return e1->type - e2->type;
    return e1->time - e2->time;
}

// Struttura e funzione di confronto per ordinare le attività in base al tempo di inizio.
typedef struct {
    int index;
    int start;
} ActivityOrder;

static int cmpActivityOrder(const void *p1, const void *p2) {
    const ActivityOrder *a1 = (const ActivityOrder *)p1;
    const ActivityOrder *a2 = (const ActivityOrder *)p2;
    return a1->start - a2->start;
}

/* ---------------- Implementazioni delle funzioni richieste ---------------- */

// 1. Verifica delle dipendenze
int ACTcheckDep(ACT a) {
    for (int i = 0; i < a.numDipendenze; i++) {
        int idx_dep = a.dipendenze[i].from;
        int idx_prereq = a.dipendenze[i].to;
        // L'attività che dipende non deve iniziare prima della fine della sua dipendenza.
        if (a.attivita[idx_dep].inizio < a.attivita[idx_prereq].fine) {
            return 0; // verifica fallita
        }
    }
    return 1; // verifica superata
}

// 2. Stampa sorgenti/pozzi o radici/foglie in base alla struttura del grafo
void ACTprintSrcSnk(ACT a) {
    int *in_degree = calloc(a.numAttivita, sizeof(int));
    int *out_degree = calloc(a.numAttivita, sizeof(int));
    
    // Conta i gradi in ingresso e in uscita per ciascuna attività.
    for (int i = 0; i < a.numDipendenze; i++) {
        int from = a.dipendenze[i].from;
        int to = a.dipendenze[i].to;
        out_degree[from]++;
        in_degree[to]++;
    }
    
    // Verifica se il grafo è una foresta (ogni attività ha al massimo un arco uscente).
    bool isForest = true;
    for (int i = 0; i < a.numAttivita; i++) {
        if (out_degree[i] > 1) {
            isForest = false;
            break;
        }
    }
    
    if (!isForest) {
        printf("Grafo delle dipendenze: DAG\n");
        printf("Sorgenti (attività con in_degree == 0): ");
        for (int i = 0; i < a.numAttivita; i++) {
            if (in_degree[i] == 0)
                printf("%s ", a.attivita[i].nome);
        }
        printf("\nPozzi (attività con out_degree == 0): ");
        for (int i = 0; i < a.numAttivita; i++) {
            if (out_degree[i] == 0)
                printf("%s ", a.attivita[i].nome);
        }
        printf("\n");
    } else {
        printf("Grafo delle dipendenze: Albero radicato / Foresta\n");
        printf("Radici (attività senza dipendenza, out_degree == 0): ");
        for (int i = 0; i < a.numAttivita; i++) {
            if (out_degree[i] == 0)
                printf("%s ", a.attivita[i].nome);
        }
        printf("\nFoglie (attività non premesse da altre, in_degree == 0): ");
        for (int i = 0; i < a.numAttivita; i++) {
            if (in_degree[i] == 0)
                printf("%s ", a.attivita[i].nome);
        }
        printf("\n");
    }
    
    free(in_degree);
    free(out_degree);
}

// 3. Calcolo del minimo numero di persone necessarie
int ACTminPers(ACT a) {
    int nEvents = 2 * a.numAttivita;
    Event *events = malloc(nEvents * sizeof(Event));
    int idx = 0;
    for (int i = 0; i < a.numAttivita; i++) {
        events[idx].time = a.attivita[i].inizio;
        events[idx].type = +1;
        idx++;
        events[idx].time = a.attivita[i].fine;
        events[idx].type = -1;
        idx++;
    }
    
    qsort(events, nEvents, sizeof(Event), cmpEvent);
    
    int current = 0, maxPers = 0;
    for (int i = 0; i < nEvents; i++) {
        current += events[i].type;
        if (current > maxPers)
            maxPers = current;
    }
    free(events);
    return maxPers;
}

// 4. Calcolo dell'assegnazione ottima delle attività
void ACTbestPlan(ACT a) {
    int N = ACTminPers(a);
    
    // Struttura per rappresentare ciascuna persona.
    typedef struct {
        int last_finish; // tempo di fine dell'ultima attività assegnata
        int total_cost;  // somma dei costi delle attività assegnate
    } Person;
    
    Person *pers = malloc(N * sizeof(Person));
    for (int i = 0; i < N; i++) {
        pers[i].last_finish = 0;  // tutti disponibili dal tempo 0
        pers[i].total_cost = 0;
    }
    
    // Creazione di un array per ordinare le attività in base al tempo di inizio.
    ActivityOrder *order = malloc(a.numAttivita * sizeof(ActivityOrder));
    for (int i = 0; i < a.numAttivita; i++) {
        order[i].index = i;
        order[i].start = a.attivita[i].inizio;
    }
    qsort(order, a.numAttivita, sizeof(ActivityOrder), cmpActivityOrder);
    
    // Assegnazione greedy: per ogni attività, assegnare la persona disponibile con minore costo accumulato.
    for (int k = 0; k < a.numAttivita; k++) {
        int idx = order[k].index;
        int best = -1;
        for (int i = 0; i < N; i++) {
            if (pers[i].last_finish <= a.attivita[idx].inizio) { // persona disponibile
                if (best == -1 || pers[i].total_cost < pers[best].total_cost)
                    best = i;
            }
        }
        if (best == -1) {
            // Questo caso non dovrebbe verificarsi se N è calcolato correttamente.
            fprintf(stderr, "Errore: nessuna persona disponibile per l'attività %s\n", a.attivita[idx].nome);
        } else {
            a.attivita[idx].assigned_to = best;
            pers[best].last_finish = a.attivita[idx].fine;
            pers[best].total_cost += a.attivita[idx].costo;
        }
    }
    
    // Stampiamo l'assegnazione per verificare il risultato.
    printf("Assegnazione attività:\n");
    for (int i = 0; i < a.numAttivita; i++) {
        printf("Attività %s assegnata a persona %d\n", a.attivita[i].nome, a.attivita[i].assigned_to);
    }
    
    free(order);
    free(pers);
}
