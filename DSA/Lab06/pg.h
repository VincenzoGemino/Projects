#ifndef PG_H_DEFINED
#define PG_H_DEFINED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inv.h>

typedef struct tabEquip_s{
    int inUso;
    inv_t *vettEq;
}tabEquip_t;

typedef struct pg_s {
    char *cod;
    char *nome;
    char *classe;
    stat_t b_stat, eq_stat;
    tabEquip_t *equip; 
} pg_t;

typedef struct nodoPg_s* linkPg;

typedef struct nodoPg_s{
    pg_t pg;
    linkPg next;
}nodoPg_t;

typedef struct tabPg_s{
    nodoPg_t head;
    nodoPg_t tail;
    int nPg;
}tabPg_t;

tabPg_t *pgInFile(char *nomeFile, )
















#endif