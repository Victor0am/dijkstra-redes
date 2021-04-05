#include <stdio.h>
#include <stdlib.h>

#include "./node.h"
#include "./edge.h"

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
    if(edge->next != NULL){
        return edge->next;
    }
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
        edge == NULL;
}

void destroy_edge_vector(Edge* edges) {
    Edge* aux;
    while (edges != NULL) {
        aux = edges;
        edges = edges->next;
        destroy_edge(aux);
    }
    free(edges);
}