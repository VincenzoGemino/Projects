#include <stdio.h>
#include <stdlib.h>

int mincd(int a, int b){
    int tmp;
    if(b > a){
        tmp = a;
        a = b;
        b = tmp;
    }
    if (a - b = 0){ //terminazione
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
    elseif(a % 2 != 0){
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