#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAXL 50
#define MAXSCELTE 8
#define MAXLF 25

typedef struct DataDiNascita{
    int gg;
    int mm;
    int aaaa;
} Data_t;

typedef struct Indirizzo_s{
    char *via;
    char *citta;
    int cap;
} indirizzo_t;

typedef struct {
    char *codice;
    char *nome;
    char *cognome;
    char *dataStr;
    Data_t d1;
    indirizzo_t ind1;
} Item;

typedef struct node_s *link;

typedef struct node_s{
    Item *val;
    link next;
} node_t;

enum {falso, vero};
typedef int bool;


int checkCodice(char *codice, link head);
int checkData(Data_t *d1, Data_t *d2, link head);
Data_t *dataTransf(char *data);
Item *ItemNew(char *codice, char *nome, char *cognome, Data_t *d1, indirizzo_t *ind1, int cap);
int stampaMenu(char *scelte[]);
link CaricaAnagrafica(char *nomefile, link head);
Item *ItemSearch(char *codice, link head);
Item *ItemDelete(char *codice, link head);
Item *ItemDateDelete(Data_t *d1, Data_t *d2, link head);
void StampaAnagrafica(Item *anag1, link head);


int main(int argc, char **argv){
    bool fineProgramma = falso;
    int selezione;

    char *scelte[] = {
    "Uscita",
    "Carica da file",
    "Aggiungi persona (tastiera)",
	"Stampa a video",
	"Stampa su file",
    "Ricerca per codice",
    "Elimina dato codice",
    "Elimina tra date"
	};

    char nomeFile[MAXLF], dataStr1[MAXL], dataStr2[MAXL];
    Data_t d1, d2;
    link head = NULL;
    Item *itp;


    do {
        selezione = stampaScelte(scelte);
        switch (selezione)
        {
        case 0:
            fineProgramma = vero;
            break;
        case 1:
            printf("nome file: \n");
            scanf("%s", nomeFile);
            head = CaricaAnagrafica(nomeFile, head);
            break;
        case 2:
            fineProgramma = vero;
            break;
        case 3:
            fineProgramma = vero;
            break;
        case 4:
            fineProgramma = vero;
            break;
        case 5:
            fineProgramma = vero;
            break;
        case 6:
            fineProgramma = vero;
            break;
        case 7:
            fineProgramma = vero;
            break;    
        
        default:
            printf("Scelta non valida!\n");
            break;
        }
    }while (fineProgramma == falso);



    return 0;
}


int stampaMenu(char *scelte[]){
    int scelta, i;
    printf("Menu\n\n");
    for(i = 0;i<MAXSCELTE;i++){printf("%2d > %s\n", i, scelte[i]);};
    scanf("%d", &scelta);
    
    return scelta;
}