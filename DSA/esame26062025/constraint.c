#include <stdlib.h>
#include <stdio.h>

#include <constraint.h>
#include <object.h>

typedef struct constraint_s{
    object_t *ogg1, *ogg2;
} constraint_t;

typedef struct {
    constraint_t *listaVincoli;
    int nVincoli;
} constraints;