#include<stdlib.h>
#include<stdio.h>
#include "edge.h"

struct edge {
    int ori;
    int dst;
    double weight;
};

Edge* init_edge (int ori, int dst, double weight) {
    Edge* new_edge = (Edge*) malloc (sizeof(Edge));
    new_edge->ori = ori;
    printf("%d ", new_edge->ori);
    new_edge->dst = dst;
    printf("%d ", new_edge->dst);
    new_edge->weight = weight;
    printf("%lf\n", new_edge->weight);

    return new_edge;
}

void show_edge (Edge* edge) {
    printf("ori: %d, dst: %d, weight: %lf\n", edge->ori, edge->dst, edge->weight);
}

void destroy_edge (Edge* edge) {
    if (edge != NULL)
        free(edge);
} 

void destroy_edge_vector (Edge** edges, int n_edges) {
    for (int i = 0; i < n_edges; i++){
        show_edge(edges[i]);
        destroy_edge(edges[i]);
    }
    free(edges);
} 