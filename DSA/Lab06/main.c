#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inv.h"
#include "pg.h"

#define SCELTE 7
#define DEBUG 0

enum {falso, vero};
typedef int bool;

void stampaMenu(char *scelte[], int *scelta){
    int i = 0;
    printf("\nMENU\n");
    for(int i=0;i<SCELTE;i++){
        printf("%2d > %s\n", i, scelte[i]);
    }
    scanf("%d", scelta);
    return;
}

int main(int argc, char **argv){
    int scelta, fineProgramma;
    char *scelte[] = {
       "Uscita",
		"Stampa personaggi",
		"Stampa inventario",
		"Cerca personaggio",
		"Aggiungi personaggio",
		"Elimina personaggio",
    "Modifica equip"
    };

    #if DBG
	     stampaTabInv(stdout, tabInv);
    #endif /* DBG */

    tabPg = leggiTabPg("pg.txt");
    if (tabPg == NULL)
		return 0;
    #if DBG
	    stampaTabPg(stdout, tabPg);
    #endif /* DBG */

    fineProgramma = falso;

    do
    {
        stampaMenu(scelte, scelta);
        switch (scelta)
        {
        case 0:
            fineProgramma = vero;
            break;
        case 0:
            ;
            break;
        case 1:
            fineProgramma = vero;
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
        default:
        printf("scelta non valida \n");
            break;
        }
    } while (fineProgramma = falso);






    return 0;
}