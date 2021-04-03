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

int get_dest(Edge* edge){
    return edge->dest;
}



double get_weight(Edge* edge){
    return edge->weight;
}

void set_weight(Edge* edge, double weight) {
    edge->weight = weight;
}

Edge* get_next(Edge* edge){
    return edge->next;
}

void set_next(Edge* edge, Edge* next) {
    edge->next = next;
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
    // free(edges);
}