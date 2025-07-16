#ifndef UF_H
#define UF_H

/** Struttura per Union-Find (disjoint-set) */
typedef struct UF UF;

/**
 * Crea una struttura UF per n elementi.
 * @param n numero di elementi
 * @return puntatore a UF allocata
 */
UF* uf_create(int n);

/**
 * Trova il rappresentante della componente di x.
 * @param u puntatore a UF
 * @param x elemento da cercare
 * @return indice del rappresentante
 */
int uf_find(UF *u, int x);

/**
 * Unisce le componenti di a e b.
 * @param u puntatore a UF
 * @param a primo elemento
 * @param b secondo elemento
 */
void uf_union(UF *u, int a, int b);

/**
 * Libera la memoria di UF.
 * @param u puntatore a UF da deallocare
 */
void uf_free(UF *u);

#endif // UF_H