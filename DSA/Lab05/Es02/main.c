/*
controllo su univocità tessera, rotazione 90°, massimo punteggio completando la scacchiera*/


#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef struct segmento_{
    int punteggio;
    char colore;
} segmento;

typedef struct tessera_{
    segmento x;
    segmento y;
} tessera;

typedef struct board_{
    int row, col;
    tessera *tessere;
} board;

tessera **boardIn(FILE *in, int nRow, int nCol, tessera tessList){
    int i, j;
    board **boardNew;
    *boardNew = malloc(nRow*sizeof(board));
    for(i=0;i<nCol;i++){
        boardNew[i] = malloc(nCol*sizeof(board));
    }
    
    for(i=0;i<nRow;i++){
        for(j=0;j<nCol;j++){
            fscanf(in, "%d/%d", &boardNew[i][j]., &tess1[i].y.punteggio);
        }
        
        printf("%c %d %c %d\n", tess1[i].x.colore,tess1[i].x.punteggio,tess1[i].y.colore,tess1[i].y.punteggio);
    }

    return tessList;
}

board *tessereIn(FILE *in, tessera *tess1, int n){
    int i;
    tessera *tessList; 
    tessList = malloc(n*sizeof(tessera));
    for(i=0;i<n;i++){
        fscanf(in, "%c %d %c %d\n",  &tess1[i].x.colore, &tess1[i].x.punteggio, &tess1[i].y.colore, &tess1[i].y.punteggio);
        printf("%c %d %c %d\n", tess1[i].x.colore,tess1[i].x.punteggio,tess1[i].y.colore,tess1[i].y.punteggio);
    }

    return tessList;
}

int main(){
    int nTessere, i, *indTessere;
    int righe, colonne;
    tessera *listaTess;
    FILE *fp;
    fp = fopen("tiles.txt", "r");
    if(fp == NULL){
        printf("Error opening file. \n");
        return -1;
    }
    fscanf(fp, "%d\n", &nTessere);
    indTessere = calloc(nTessere-1,sizeof(int));
    listaTess = tessereIn(fp, listaTess, nTessere);
    fclose(fp);

    fp = fopen("board.txt", "r+w");
    if(fp == NULL){
        printf("Error opening file. \n");
        return -2;
    }
    fscanf(fp, "%d %d\n", &righe, &colonne);
    boardIn(fp, righe, colonne, listaTess);

    return 0;
}