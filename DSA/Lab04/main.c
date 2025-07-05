#include <stdlib.h>
#include <stdio.h>

//struttura dati

typedef struct arco_s{
  int u;
  int v;
} arco;

arco *leggiFile(char *nomeFile,int *N, int *E){
  int i;
  arco *a;
  FILE *in = fopen(nomeFile, "r");
  if(in == NULL){
    exit(-1);
  }

  fscanf(in, "%d %d", N, E);
  a = (arco *)calloc(*E, sizeof(arco));
  if(a == NULL){
    exit(-1);
  }

  for(i=0;i<*E;i++){
    fscanf(in, "%d %d", &a[i].u, &a[i].v);
  }
  return a;
}

int powerset_disp_rip(int pos, int *sol, int N, int E, arco *a, int count);
int check(int *sol, int N, arco *a, int E){
  int i, ok = 1;
  for(i=0;i<N;i++){
    if(sol[a[i].u] == 0 && sol[a[i].v] == 0){
      ok = 0;
      return ok;
    }
  }
  return ok;
}
int main() {
  int N = -1, E = -1, cnt;
  int *sol;
  arco *a = leggiFile("grafo.txt", &N, &E);
  cnt = powerset_disp_rip(0, sol, N, E, a, cnt);
  printf("Numero di sottoinsiemi: %d", cnt);
    return 0;
}

int powerset_disp_rip(int pos, int *sol, int N, int E, arco *a, int count){
  int i;
  if(pos>=N){
    if((check(sol, N, a, E)) == 1){
      printf("{");
      for(i=0;i<N;i++){
        if(sol[i] == 1){
          printf("%d", i);
        }
      }
      printf("}\n");
      return count+1;
    }
    return count;
  }

  sol[pos] = 0;
  powerset_disp_rip(pos+1, sol, N, E, a, count);
  sol[pos] = 1;
  powerset_disp_rip(pos+1, sol, N, E, a, count);

}