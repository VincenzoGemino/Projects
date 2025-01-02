#include <stdio.h>
#include <stdlib.h>

int mincd(int a, int b){
    int tmp;

    //cambio se b > a
    if(b > a){
        tmp = a;
        a = b;
        b = tmp;
    }

    //terminazione
    if (a - b == 0){ 
        return b;
    }

    //non terminazione
    if((a % 2) == 0){
        if ((b % 2) == 0){
            2 * mincd(a/2, b/2);
        }
        else{
            mincd(a/2, b);
        }
    }
    if(a % 2 != 0){
        if(b % 2 == 0){
            mincd(a, b/2);
        }
        else{
            mincd((a-b)/2, b);
        }
    }
    else{
        printf("errore\n");
    };
}



int main(){
    int a, b, tmp = 0;
    scanf("%d %d", &a, &b);
    
    tmp = mincd(a, b);
    printf("%d", tmp);

    return 0;
}

//risoluzione errata: occorreva verificare che per ogni singolo caso ci fosse un return, altrimenti occorre un puntatore per la modifica di tmp
//altra problematica: riguardare la soluzione ritornata