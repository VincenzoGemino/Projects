#ifndef OBJECTS_H
#define OBJECTS_H

#include <stddef.h>

#define MAX_NAME_LEN 31

typedef struct {
    char name[MAX_NAME_LEN];
    double cost;
    double weight;
    double volume;
} Object;

typedef struct {
    Object *arr;
    int n;
} Objects;

/**
 * Carica gli oggetti da file di testo.
 * @param fname percorso del file
 * @return puntatore a struttura Objects allocata
 */
Objects* load_objects(const char *fname);

/**
 * Cerca un oggetto per nome all'interno di Objects.
 * @param objs puntatore a Objects
 * @param name nome dell'oggetto
 * @return puntatore all'Object trovato, NULL se non trovato
 */
Object* find_object(const Objects *objs, const char *name);

/**
 * Libera la memoria allocata per Objects.
 * @param objs puntatore a Objects da deallocare
 */
void free_objects(Objects *objs);

#endif // OBJECTS_H
