#include <ACT.h>

//strutture dati e funzioni addizionali di supporto per i problemi di ricerca e ottimizzazione

typedef struct { // struttura dati per implementare un evento
    int tempo;
    int tipoT; // +1: inizio, -1: fine
} Evento;

static int cmpEvento(const void *p1, const void *p2) { // funzione di comparazione per eventi
    const Evento *ev1 = (const Evento *)p1;
    const Evento *ev2 = (const Evento *)p2;
    if (e1->time == e2->time)
        return e1->type - e2->type;
    return e1->time - e2->time;
}

// Struttura e funzione di confronto per ordinare le attività in base al tempo di inizio.
typedef struct {
    int indice;
    int tInizio;
} ordineAttività;

static int cmpordineAttività(const void *p1, const void *p2) {
    const ordineAttività *att1 = (const ordineAttività *)p1;
    const ordineAttività *att2 = (const ordineAttività *)p2;
    return att1->tInizio - att2->tInizio;
}

//funzioni richieste

int ACTcheckDep(ACT a) { //Utilizzando gli indici da struttura dati Dipendenza, non c'è la necessità di un confronto tra nomi delle attività dipendenti.
                         //Questo permette di effettuare un singolo ciclo for, utilizzando l'indice memorizzato nel vettore delle dipendenze per risalire all'attività,
                         //sia essa dipendente, o da cui dipende.
    for (int i = 0; i < a.nAtt; i++) {
        int iDipSucc = a.dip[i].succ; //memorizzo localmente l'indice dell'attività successiva, che, quindi, dipende 
        int iDipPrec = a.dip[i].preced; // memorizzo localmente l'indice dell'attività precedente, da cui dipende la successiva
        // L'attività che dipende non deve iniziare prima della fine della sua dipendenza.
        if (a.act[iDipSucc].tIni < a.act[iDipPrec].tFin) {
            return 0; // verifica fallita
        }
    }
    return 1; // verifica superata
}

void ACTprintSrcSnk(ACT a) {

    int *gradoIn = calloc(a.nAtt, sizeof(int)); //utilizzo un vettore allocato dinamicamente per determinare per ogni vertice, gli archi in ingresso
    int *gradoOut = calloc(a.nAtt, sizeof(int)); //utilizzo un vettore allocato dinamicamente per determinare per ogni vertice, gli archi in uscita
    
    // Conta gli archi in ingresso e in uscita per ogni attività
    for (int i = 0; i < a.nDip; i++) {
        int succ = a.dip[i].succ;
        int preced = a.dip[i].preced;
        gradoOut[succ]++; //incremento il numero di volte in cui, per l'attività all'indice succ, gli archi uscenti (dipendenze)
        gradoIn[preced]++; //incremento il numero di volte in cui, per l'attività all'indice preced, gli archi entranti
    }
    
    // Verifica se il grafo è una foresta (ogni attività ha al massimo un arco uscente)
    bool isForest = true;
    for (int i = 0; i < a.nAtt; i++) {
        if (gradoOut[i] > 1) {
            isForest = false;
            break;
        }
    }
    
    if (!isForest) {
        printf("Grafo delle dipendenze: DAG\n");
        printf("Sorgenti (attività con gradoIn == 0): ");
        for (int i = 0; i < a.nAtt; i++) {
            if (gradoIn[i] == 0)
                printf("%s ", a.act[i].nome);
        }
        printf("\nPozzi (attività con gradoOut == 0): ");
        for (int i = 0; i < a.nAtt; i++) {
            if (gradoOut[i] == 0)
                printf("%s ", a.act[i].nome);
        }
        printf("\n");
    } else {
        printf("Grafo delle dipendenze: Albero - Foresta\n");
        printf("Radici (attività con gradoIn == 0): ");
        for (int i = 0; i < a.nAtt; i++) {
            if (gradoIn[i] == 0)
                printf("%s ", a.act[i].nome);
        }
        printf("\nFoglie (attività con gradoOut == 0): ");
        for (int i = 0; i < a.nAtt; i++) {
            if (gradoOut[i] == 0)
                printf("%s ", a.act[i].nome);
        }
        printf("\n");
    }
    
    free(gradoIn);
    free(gradoOut);
}

int ACTminPers(ACT a) {
    int nEventi = 2 * a.nAtt;
    Evento *eventi = malloc(nEventi * sizeof(Evento));
    int ind = 0;
    for (int i = 0; i < a.nAtt; i++) {
        eventi[ind].tempo = a.act[i].tIni;
        eventi[ind].tipoT = 1;
        ind++;
        eventi[ind].tempo = a.act[i].tFin;
        eventi[ind].tipoT = -1;
        ind++;
    }
    
    qsort(eventi, nEventi, sizeof(Evento), cmpEvento);
    
    int curr = 0, maxPersone = 0;
    for (int i = 0; i < nEventi; i++) {
        curr += eventi[i].tipoT;
        if (curr > maxPersone)
            maxPersone = curr;
    }
    free(eventi);
    return maxPersone;
}

// 4. Calcolo dell'assegnazione ottima delle attività
void ACTbestPlan(ACT a) {
    int N = ACTminPers(a);
    
    // Struttura per rappresentare ciascuna persona.
    typedef struct {
        int attFine; // tempo di fine dell'ultima attività assegnata
        int costiTot;  // somma dei costi delle attività assegnate
    } Persona;
    
    Persona *pers = malloc(N * sizeof(Persona));
    for (int i = 0; i < N; i++) {
        pers[i].attFine = 0;  // tutti disponibili dal tempo 0
        pers[i].costiTot = 0;
    }
    
    // Creazione di un array per ordinare le attività in base al tempo di inizio.
    ordineAttività *ordine = malloc(a.nAtt * sizeof(ordineAttività));
    for (int i = 0; i < a.nAtt; i++) {
        ordine[i].indice = i;
        ordine[i].tInizio = a.act[i].tIni;
    }
    qsort(ordine, a.nAtt, sizeof(ordineAttività), cmpordineAttività);
    
    // Assegnazione greedy: per ogni attività, assegnare la persona disponibile con minore costo accumulato.
    for (int k = 0; k < a.nAtt; k++) {
        int ind = ordine[k].indice;
        int best = -1;
        for (int i = 0; i < N; i++) {
            if (pers[i].attFine <= a.act[ind].tIni) { // persona disponibile
                if (best == -1 || pers[i].costiTot < pers[best].costiTot)
                    best = i;
            }
        }
        if (best == -1) {
            // Questo caso non dovrebbe verificarsi se N è calcolato correttamente.
            fprintf(stderr, "Errore: nessuna persona disponibile per l'attività %s\n", a.act[ind].nome);
        } else {
            a.act[ind].assegnatoA = best;
            pers[best].attFine = a.act[ind].tFin;
            pers[best].costiTot += a.act[ind].costo;
        }
    }
    
    // Stampiamo l'assegnazione per verificare il risultato.
    printf("Assegnazione attività:\n");
    for (int i = 0; i < a.nAtt; i++) {
        printf("Attività %s assegnata a persona %d\n", a.act[i].nome, a.act[i].assegnatoA);
    }
    
    free(ordine);
    free(pers);
}