#include <stdio.h>
#include <stdlib.h>

int majority(int *a, int N){
    return 
}

int main(){
    int n, *a;
    printf("Inserisci lunghezza vettore:");
    scanf("%d", &n);
    a = (int *)malloc(n*(sizeof(int)));
    if(a == NULL) exit(1);

    printf("Inserisci %d elementi\n", n);
    for(int i = 0; i < n; i++){
        printf("El. %d: ", i);
        scanf("%d", &a[i]);
    }

    

    free(a);

    return 0;
}