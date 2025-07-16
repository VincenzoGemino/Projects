#include <stdlib.h>
#include "uf.h"

struct UF {
    int *parent;
    int *rank;
    int n;
};

UF* uf_create(int n) {
    UF *u = malloc(sizeof(UF));
    u->n = n;
    u->parent = malloc(n * sizeof(int));
    u->rank = calloc(n, sizeof(int));
    for (int i = 0; i < n; ++i)
        u->parent[i] = i;
    return u;
}

int uf_find(UF *u, int x) {
    if (u->parent[x] != x)
        u->parent[x] = uf_find(u, u->parent[x]);
    return u->parent[x];
}

void uf_union(UF *u, int a, int b) {
    int ra = uf_find(u, a);
    int rb = uf_find(u, b);
    if (ra == rb) return;
    if (u->rank[ra] < u->rank[rb])
        u->parent[ra] = rb;
    else if (u->rank[ra] > u->rank[rb])
        u->parent[rb] = ra;
    else {
        u->parent[rb] = ra;
        u->rank[ra]++;
    }
}

void uf_free(UF *u) {
    free(u->parent);
    free(u->rank);
    free(u);
}