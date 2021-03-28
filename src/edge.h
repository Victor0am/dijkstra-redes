#ifndef EDGE_H
#define EDGE_H

typedef struct edge Edge;

Edge* init_edge (int ori, int dst, double weight);

void show_edge (Edge* edge);

void destroy_edge (Edge* edge);

void destroy_edge_vector (Edge** edges, int n_edges);

#endif