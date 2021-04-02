#ifndef EDGE_H
#define EDGE_H

typedef struct edge Edge;

Edge* init_edge_list(int dst, double weight);

void add_edge(Node* node, int dest, double weight);

void show_edge(Edge* edge);

void destroy_edge(Edge* edge);

void destroy_edge_vector(Edge* edges);

#endif