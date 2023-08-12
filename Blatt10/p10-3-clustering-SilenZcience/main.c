#include "unionfind.h"
#include "mergesort.h"
#include "graph.h"

#include <stdio.h>
#include <stdlib.h>

/* (Modifizierter) Algorithmus von Kruskal: Stoppe vorzeitig, wenn der
 * Graph k Zusammenhangskomponenten hat.
 *
 * Eingabe: (unsortiertes) Kantenarray edges (s. Graph.h), Anzahl
 *          Knoten und Kanten im Graphen (letzteres ist die Länge
 *          von edges). Gewünschte Anzahl an Clustern k.
 */
UFNode* kruskal(Edge* edges, int n_nodes, int n_edges, int k) {
    // Wir verwenden UnionFind, um die Cluster abzubilden.
    // Initial ist jeder Knoten allein in seinem Cluster
    UFNode* clusters = malloc(n_nodes * sizeof(UFNode));
    for(int i=0; i < n_nodes; ++i) {
        uf_init(&clusters[i], i);
    }

    // Sort all edges in regard to the square distance
    merge_sort_bottom_up(edges, n_edges);

    int n_clusters = n_nodes;

    for (int i = 0; i < n_edges; i++) {
        Edge e = edges[i];
        if (uf_find(&clusters[e.src]) != uf_find(&clusters[e.tgt])) {
            // keep track of the amount of clusters each time we uf_union
            n_clusters--;
            uf_union(&clusters[e.src], &clusters[e.tgt]);
        }
        // stop when we have few enough clusters
        if (n_clusters <= k) {
            break;
        }
    }

    return clusters;
}

/* Unter dieser Zeile darf/muss nichts verändert werden :) */
int main(int argn, char** argv) {
    int n_nodes, n_edges, n_clusters;
    Edge* edges = read_edges(stdin, &n_nodes, &n_edges, &n_clusters);
    if(edges == NULL) {
        fprintf(stderr, "Fehler: Konnte Eingabe nicht lesen.\n");
        return 0;
    }

    UFNode* clusters = kruskal(edges, n_nodes, n_edges, n_clusters);
    print_clusters(stdout, clusters, n_nodes, n_clusters);

    free(edges);
    free(clusters);

    return 0;
}


