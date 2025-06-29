#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include "sol.h"

typedef struct Sol {
    int *day;
    int days;
    double cost_diff;
} Sol;

Sol* sol_create(int C) {
    Sol *s = malloc(sizeof(Sol));
    s->days = 0;
    s->cost_diff = DBL_MAX;
    s->day = malloc(C * sizeof(int));
    return s;
}

typedef struct {
    double cost;
    double weight;
    double volume;
} Comp;

static void rec_assign(int idx, int used_days,
                       double *w_day, double *v_day, double *c_day,
                       int C, double Pmax, double Vmax,
                       Comp *comps, Sol *curr, Sol *best) {
    if (idx == C) {
        double c_max = 0, c_min = DBL_MAX;
        for (int d = 0; d < used_days; ++d) {
            c_max = fmax(c_max, c_day[d]);
            c_min = fmin(c_min, c_day[d]);
        }
        double diff = c_max - c_min;
        if (used_days < best->days ||
           (used_days == best->days && diff < best->cost_diff)) {
            best->days = used_days;
            best->cost_diff = diff;
            memcpy(best->day, curr->day, C * sizeof(int));
        }
        return;
    }
    if (used_days > best->days) return;
    for (int d = 0; d < used_days; ++d) {
        if (w_day[d] + comps[idx].weight <= Pmax &&
            v_day[d] + comps[idx].volume <= Vmax) {
            w_day[d] += comps[idx].weight;
            v_day[d] += comps[idx].volume;
            c_day[d] += comps[idx].cost;
            curr->day[idx] = d;
            rec_assign(idx+1, used_days, w_day, v_day, c_day,
                       C, Pmax, Vmax, comps, curr, best);
            w_day[d] -= comps[idx].weight;
            v_day[d] -= comps[idx].volume;
            c_day[d] -= comps[idx].cost;
        }
    }
    if (used_days + 1 < best->days) {
        w_day[used_days] = comps[idx].weight;
        v_day[used_days] = comps[idx].volume;
        c_day[used_days] = comps[idx].cost;
        curr->day[idx] = used_days;
        rec_assign(idx+1, used_days+1, w_day, v_day, c_day,
                   C, Pmax, Vmax, comps, curr, best);
    }
}

Sol* solve(Objects *objs, UF *u, double Pmax, double Vmax) {
    int n = objs->n;
    int *map = malloc(n * sizeof(int));
    int C = 0;
    for (int i = 0; i < n; ++i)
        if (uf_find(u, i) == i) map[i] = C++;
    for (int i = 0; i < n; ++i)
        map[i] = map[uf_find(u, i)];
    Comp *comps = calloc(C, sizeof(Comp));
    for (int i = 0; i < n; ++i) {
        int ci = map[i];
        comps[ci].cost   += objs->arr[i].cost;
        comps[ci].weight += objs->arr[i].weight;
        comps[ci].volume += objs->arr[i].volume;
    }
    free(map);
    Sol *best = sol_create(C);
    best->days = C + 1;
    Sol *curr = sol_create(C);
    curr->days = 0;
    curr->cost_diff = DBL_MAX;
    double *w_day = calloc(C, sizeof(double));
    double *v_day = calloc(C, sizeof(double));
    double *c_day = calloc(C, sizeof(double));
    rec_assign(0, 0, w_day, v_day, c_day,
               C, Pmax, Vmax, comps, curr, best);
    free(w_day); free(v_day); free(c_day);
    free(comps);
    sol_free(curr);
    return best;
}

void sol_free(Sol *s) {
    free(s->day);
    free(s);
}