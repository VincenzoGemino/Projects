#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "objects.h"

Objects* load_objects(const char *fname) {
    FILE *f = fopen(fname, "r");
    if (!f) return NULL;
    Objects *objs = malloc(sizeof(Objects));
    objs->n = 0;
    objs->arr = NULL;
    Object tmp;
    while (fscanf(f, "%30s %lf %lf %lf", tmp.name, &tmp.cost, &tmp.weight, &tmp.volume) == 4) {
        objs->arr = realloc(objs->arr, (objs->n + 1) * sizeof(Object));
        objs->arr[objs->n++] = tmp;
    }
    fclose(f);
    return objs;
}

Object* find_object(const Objects *objs, const char *name) {
    for (int i = 0; i < objs->n; ++i) {
        if (strcmp(objs->arr[i].name, name) == 0)
            return &((Object*)objs->arr)[i];
    }
    return NULL;
}

void free_objects(Objects *objs) {
    free(objs->arr);
    free(objs);
}