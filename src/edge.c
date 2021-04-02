#include "edge.h"

#include <stdio.h>
#include <stdlib.h>

#include "node.h"

struct edge {
    Edge* next;
    int dest;
    double weight;
};

Edge* init_edge_list(int dest, double weight) {
    Edge* new_edge = (Edge*)malloc(sizeof(Edge));
    new_edge->next = NULL;
    new_edge->dest = dest;
    new_edge->weight = weight;

    return new_edge;
}

void add_edge(Node* node, int dest, double weight) {
    Edge* w = get_w(node);
    Edge* new_edge = (Edge*)malloc(sizeof(Edge));
    if (w != NULL) {
        new_edge->next = w;
    }
    set_w(node, new_edge);
    new_edge->dest = dest;
    new_edge->weight = weight;
}

void show_edge(Edge* edge) {
    printf("dst: %d, weight: %lf\n", edge->dest, edge->weight);
}

void destroy_edge(Edge* edge) {
    if (edge != NULL)
        free(edge);
}

void destroy_edge_vector(Edge* edges) {
    while (edges != NULL) {
        Edge* aux = edges->next;
        destroy_edge(edges);
        edges = aux;
    }
    //free(edges);
}