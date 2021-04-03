#ifndef EDGE_H
#define EDGE_H


typedef struct edge Edge;

Edge* init_edge_list(int dest, double weight);

int get_dest(Edge* edge);

double get_weight(Edge* edge);

void set_next(Edge* edge, Edge* next);

Edge* get_next(Edge* edge);

void set_weight(Edge* edge, double weight);

void show_edge(Edge* edge);

void destroy_edge(Edge* edge);

void destroy_edge_vector(Edge* edges);

#endif