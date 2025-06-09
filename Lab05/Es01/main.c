/*  struct att {int s, int f};
    int d = f - s;
    att *v;

    controllo:
        checkIncomp(att a1, att a2)
            a1.s < a2.f || a2.s < a1.f
    
    richiesta:
        void attSel(int N, att *v); funzione wrapper
        dispRipetute(); funzione ricorsiva per determinare e visualizzare
*/

#include "stdio.h"
#include "stdlib.h"

typedef struct {
    int s;
    int f;
} att;

att *collInput(FILE *in, int *n);
int checkIncomp(att *a1, att *a2);
void attSel(int N, att *v);
void attSelR(int pos, int n, att *v, int *sol, int *bestSol, int currDurata, int *bestDurata);

int main(int argc, char **argv){
    int n;
    FILE *fp = fopen("collection.txt", "r");
    if(fp == NULL){return -1;}
    att *v;
    v = collInput(fp, &n);
    attSel(n, v);
    fclose(fp);
    return 0;
}

att *collInput(FILE *in, int *n){
    int i;
    att *v;
    fscanf(in, "%d\n", n);
    v = calloc(*n, sizeof(att));
    for(i=0;i<*n;i++){
        fscanf(in, "%d %d\n", &v[i].s, &v[i].f);
    }
    return v;
}


int checkIncomp(att *a1, att *a2){
    if (a1->s < a2->f || a2->s < a1->f){
        return 0;
    }
    return 1;
}

void attSel(int N, att *v){
    int *sol = calloc(N, sizeof(int));
    int *bestSol = calloc(N, sizeof(int));
    int duration = 0, i;

    attSelR(0, N, v, sol, bestSol, 0, &duration);
    printf("soluzione a durata complessiva massima %d\n", &duration);
    for(i = 0; i < N; i++){
        if(bestSol[i]){
            printf("(%d,%d)", v[i].s, v[i].f);
        }
        
    }
    printf("\n");
    free(sol);
    free(bestSol);
    return;
}

void attSelR(int pos, int n, att *v, int *sol, int *bestSol, int currDurata, int *bestDurata){
    int i;
    if(pos>= n){
        if(*bestDurata < currDurata){
            *bestDurata = currDurata;
            for(i = 0; i < n; i++){
                bestSol[i] = sol[i];
            }
        }
    }
    sol[pos] = 0;
    attSelR(pos+1, n, v, sol, bestSol, currDurata, bestDurata);
    if(!checkIncomp){
        sol[pos] = 1;
        attSelR(pos+1, n, v, sol, bestSol, currDurata+, bestDurata);
    }
    
    return;
}


