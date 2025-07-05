#include <stdio.h>
#include <stdlib.h>

#include "objects.h"
#include "uf.h"
#include "sol.h"

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s objects.txt constraints.txt Pmax Vmax\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *obj_file = argv[1];
    const char *con_file = argv[2];
    double Pmax = atof(argv[3]);
    double Vmax = atof(argv[4]);

    // Carica oggetti
    Objects *objs = load_objects(obj_file);
    if (!objs) {
        fprintf(stderr, "Errore caricamento oggetti\n");
        return EXIT_FAILURE;
    }

    // Inizializza union-find per n oggetti
    UF *u = uf_create(objs->n);
    if (!u) {
        fprintf(stderr, "Errore UF\n");
        free_objects(objs);
        return EXIT_FAILURE;
    }

    // Leggi vincoli
    FILE *f = fopen(con_file, "r");
    if (!f) {
        perror("fopen constraints");
        uf_free(u);
        free_objects(objs);
        return EXIT_FAILURE;
    }
    char a[MAX_NAME_LEN], b[MAX_NAME_LEN];
    while (fscanf(f, "%30s %30s", a, b) == 2) {
        Object *oa = find_object(objs, a);
        Object *ob = find_object(objs, b);
        if (oa && ob) {
            int ia = oa - objs->arr;
            int ib = ob - objs->arr;
            uf_union(u, ia, ib);
        }
    }
    fclose(f);

    // Verifica vincoli
    if (!verify(objs, u, Pmax, Vmax)) {
        fprintf(stderr, "Vincoli non soddisfatti: infeasible\n");
        uf_free(u);
        free_objects(objs);
        return EXIT_FAILURE;
    }

    // Risolvi
    Sol *sol = solve(objs, u, Pmax, Vmax);
    printf("Numero giorni: %d\n", sol->days);
    // Stampa assegnamenti
    for (int ci = 0; ci < sol->days; ++ci) {
        printf("Giorno %d: ", ci+1);
        for (int j = 0; j < objs->n; ++j) {
            if (sol->day[j] == ci)
                printf("%s ", objs->arr[j].name);
        }
        printf("\n");
    }

    // Cleanup
    sol_free(sol);
    uf_free(u);
    free_objects(objs);
    return EXIT_SUCCESS;
}