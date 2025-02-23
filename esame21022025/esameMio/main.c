#include "act.h"
#include <string.h>

int main(void) {
    /* Esempio di dati:
       Attività:
         0: "A1A"   (inizio=1, fine=4, costo=12)
         1: "BB75"  (inizio=12, fine=14, costo=270)
         2: "AB12B" (inizio=0, fine=6, costo=201)
         3: "ADD"   (inizio=5, fine=7, costo=45)
         4: "A4"    (inizio=3, fine=5, costo=36)
         5: "CNT3"  (inizio=5, fine=9, costo=74)
         6: "T3B"   (inizio=8, fine=11, costo=130)
         7: "YA"    (inizio=6, fine=10, costo=103)
       
       Dipendenze (interpretate come (from, to)):
         (3, 0)   -> "ADD" non può iniziare prima della fine di "A1A"
         (6, 3)   -> "T3B" non può iniziare prima della fine di "ADD"
         (6, 2)   -> "T3B" non può iniziare prima della fine di "AB12B"
         (5, 4)   -> "CNT3" non può iniziare prima della fine di "A4"
    */
    
    // Creazione delle attività
    int numAttivita = 8;
    Attivita attivita[] = {
        {"A1A",   1,  4,  12, -1},
        {"BB75", 12, 14, 270, -1},
        {"AB12B", 0,  6, 201, -1},
        {"ADD",   5,  7,  45, -1},
        {"A4",    3,  5,  36, -1},
        {"CNT3",  5,  9,  74, -1},
        {"T3B",   8, 11, 130, -1},
        {"YA",    6, 10, 103, -1}
    };
    
    // Creazione delle dipendenze
    int numDipendenze = 4;
    Dipendenza dipendenze[] = {
        {3, 0},  // ADD dipende da A1A
        {6, 3},  // T3B dipende da ADD
        {6, 2},  // T3B dipende da AB12B
        {5, 4}   // CNT3 dipende da A4
    };
    
    // Inizializzazione della struttura ACT
    ACT a;
    a.act = attivita;
    a.nAtt = numAttivita;
    a.dip = dipendenze;
    a.nDip = numDipendenze;
    
    // Verifica delle dipendenze
    if (!ACTcheckDep(a)) {
        printf("Errore: alcune dipendenze non sono rispettate.\n");
        return 1;
    } else {
        printf("Verifica dipendenze superata.\n");
    }
    
    // Stampa sorgenti/pozzi o radici/foglie
    ACTprintSrcSnk(a);
    
    // Calcolo del numero minimo di persone e assegnazione ottima delle attività
    int minPers = ACTminPers(a);
    printf("Numero minimo di persone necessarie: %d\n", minPers);
    
    ACTbestPlan(a);
    
    return 0;
}
