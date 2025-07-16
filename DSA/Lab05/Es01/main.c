/*Esplorazione dello spazio delle soluzioni con i modelli del calcolo
combinatorio e ottimizzazione*/
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct {
    int ini;
    int fin;
    int dur;
} att;

att *initAtt(FILE *in, int *n){
    int i;
    att *v;
    fscanf(in, "%d\n", n);
    v = calloc(*n, sizeof(att));
    for(i=0;i<*n;i++){
        fscanf(in, "%d %d\n", &v[i].ini, &v[i].fin);
        v[i].dur = v[i].fin - v[i].ini;
    }
    return v;
}

int check(int n, att *v, int *sol, int pos){
    int i;
    for(i=0;i<n;i++){
        if (sol[i] != 0){
            if (v[i].ini < v[pos].fin && v[pos].ini < v[i].fin)
            return 1;
        }
    }
    return 0;
}

void attSelR(int pos, att *v, int N, int *currSol, int *bestSol, int currDurata, int* bestDurata){
    int i;
    printf("%d\n", pos);
    if(pos >= N){
        if (*bestDurata < currDurata) {
            *bestDurata = currDurata;
            for (i=0; i<N; i++){
                bestSol[i] = currSol[i];
            }
            for(i=0;i<N;i++){
                printf("%d\t", *bestSol);
            }
        }
        printf("endR\n"); 
        return;
    }

    currSol[pos] = 0;
    attSelR(pos+1, v, N, currSol, bestSol, currDurata, bestDurata);
    
    if (!check(N, v, currSol, pos)) {
        printf("\t%d\n", pos);
        currSol[pos] = 1;
        attSelR(pos+1, v, N, currSol, bestSol, currDurata + v[pos].dur, bestDurata);
    }
    
    
}

void attSel(int N, att *v){
    int *currSol = calloc(N, sizeof(int));
    int *bestSol = calloc(N, sizeof(int));
    int duration = 0;
    int i;

    attSelR(0, v, N, currSol, bestSol, 0, &duration);
    printf("Soluzione a durata massima: %d\n", duration);
    for(i=0;i<N;i++){
        if(bestSol[i]){
            printf("%d %d\n", v[i].ini, v[i].fin);
        }
    }
    free(currSol);
    free(bestSol);
    return;
}

int main(){
    FILE *fp;
    int n;
    att *v;
    fp = fopen("collection.txt", "r");
    if (fp == NULL){
        exit(-1);
    }
    v = initAtt(fp, &n);
    attSel(n, v);

    fclose(fp);
    return 0;
}