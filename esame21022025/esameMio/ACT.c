#include <ACT.h>

int ACTcheckDep(ACT a) {
    for (int i = 0; i < a.nAtt; i++) {
        
        // L'attività che dipende non deve iniziare prima della fine della sua dipendenza.
        if (a.attivita[idx_dep].inizio < a.attivita[idx_prereq].fine) {
            return 0; // verifica fallita
        }
    }
    return 1; // verifica superata
}