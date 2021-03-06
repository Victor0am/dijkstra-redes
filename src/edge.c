#include "./edge.h"

#include <stdio.h>
#include <stdlib.h>

#include "./node.h"

// next - proximo item da lista
// dest - destino da aresta direcionada
// double weight - peso da aresta direcionada
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

int get_dest(Edge* edge) {
    return edge->dest;
}

double get_weight(Edge* edge) {
    return edge->weight;
}

Edge* get_next(Edge* edge) {
    if (edge->next != NULL) {
        return edge->next;
    }
}

void set_next(Edge* edge, Edge* next) {
    edge->next = next;
}

void destroy_edge(Edge* edge) {
    if (edge != NULL)
        free(edge);
}

void destroy_edge_list(Edge* edges) {
    Edge* aux;
    while (edges != NULL) {
        aux = edges;
        edges = edges->next;
        destroy_edge(aux);
    }
    free(edges);
}