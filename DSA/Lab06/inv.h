#ifndef INV_H_DEFINED
#define INV_H_DEFINED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stat_s{
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
}stat_t;

typedef struct inv_s{
    char *nome;
    char *tipo;
    stat_t stat;
}inv_t;

typedef struct tabinv_s{
    inv_t *vettInv;
    int nInv;
    int maxInv;
}tabinv_t;

tabinv_t *leggiFileInv(char *nomeFile);
void leggiInv(FILE *fp, inv_t *inv);
void stampaInv(FILE *fp, inv_t inv);

inv_t ricercaOgg(char *nomeOggetto, tabinv_t *listaOggetti);
void stampaDettOgg(inv_t oggetto);

#endif