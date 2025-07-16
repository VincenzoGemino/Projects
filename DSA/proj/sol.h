#ifndef SOL_H
#define SOL_H

#include "objects.h"
#include "uf.h"

/** Struttura che rappresenta la soluzione dell'assegnamento */
typedef struct Sol Sol;

/**
 * Verifica se tutti i gruppi connessi rispettano Pmax e Vmax.
 * @param objs puntatore a Objects
 * @param u puntatore a UF con i vincoli
 * @param Pmax capacità peso giornaliera
 * @param Vmax capacità volume giornaliera
 * @return 1 se fattibile, 0 altrimenti
 */
int verify(Objects *objs, UF *u, double Pmax, double Vmax);

/**
 * Risolve il problema assegnando le componenti ai giorni.
 * Minimizza giorni e differenza di costo.
 * @param objs puntatore a Objects
 * @param u puntatore a UF con i vincoli
 * @param Pmax capacità peso giornaliera
 * @param Vmax capacità volume giornaliera
 * @return puntatore a Sol allocata (da free con sol_free)
 */
Sol* solve(Objects *objs, UF *u, double Pmax, double Vmax);

/**
 * Libera la memoria di Sol.
 * @param s puntatore a Sol da deallocare
 */
void sol_free(Sol *s);

#endif // SOL_H