#include "graph.h"
#include "unionfind.h"

#include <stdio.h>
#include <stdlib.h>

int sq_dist(int px, int py, int qx, int qy) {
    return (px - qx)*(px - qx) + (py - qy)*(py - qy);
}

Edge* read_edges(FILE* f, int* n_points, int* n_edges, int* n_clusters) {
    if(fscanf(f, "%d %d\n", n_points, n_clusters) != 2) {
        fprintf(stderr, "Fehler: Konnte Anzahl Punkte/Cluster nicht lesen.\n");
        return NULL;
    }

    int* x = calloc(*n_points, sizeof(int));
    int* y = calloc(*n_points, sizeof(int));

    for(int i=0; i < *n_points; ++i) {
        if(fscanf(f, "%u %u", &x[i], &y[i]) != 2) {
            fprintf(stderr, "Fehler: Punkt %d nicht lesen.\n", i);
            free(x);
            free(y);
            return NULL;
        }
    }

    *n_edges = (*n_points*(*n_points - 1)) / 2;
    Edge* edges = calloc(*n_edges, sizeof(Edge));
    Edge* e = edges;
    for(int i=0; i < *n_points; ++i) {
        for(int j=i+1; j < *n_points; ++j) {
            e->src = i;
            e->tgt = j;
            e->length = sq_dist(x[i], y[i], x[j], y[j]);
            ++e;
        }
    }

    free(x);
    free(y);

    return edges;
}

void print_edge(FILE* f, Edge e) {
    fprintf(f, "%u -[%lu]-> %u", e.src, e.length, e.tgt);
}

void print_edges(FILE* f, Edge* adj, int n_edges) {
    for(int i=0; i < n_edges; ++i) {
        print_edge(f, adj[i]);
        fprintf(f, "\n");
    }
}

void print_clusters(FILE* f, UFNode* clusters, int n_points, int n_clusters) {
    int** c = malloc(n_points*sizeof(int*));
    for(int i=0; i < n_points; ++i) c[i] = malloc(n_points*sizeof(int));

    int* size = calloc(n_points, sizeof(int));

    for(int i=0; i < n_points; ++i) {
        const int c_idx = uf_find(&clusters[i])->key;
        c[c_idx][size[c_idx]] = clusters[i].key;
        ++size[c_idx];
    }

    int n_printed = 1;
    for(int i=0; i < n_points; ++i) {
        if(size[i] == 0) continue;

        fprintf(f, "Cluster %d: ", n_printed);
        for(int j=0; j < size[i]; ++j) {
            fprintf(f, "%d ", c[i][j]);
        }
        fprintf(f, "\n");
        ++n_printed;
    }

    for(int i=0; i < n_points; ++i) free(c[i]);
    free(c);
    free(size);
}

