 #include <stdlib.h>
 #include <stdio.h>

 #include <object.h>
 #define MAXC 30

typedef struct object_s {
    char nome[MAXC];
    int costo, peso, volume;
} object_t;

typedef struct {
    object_t *listaOgg;
    int nOggetti;
} objects;
