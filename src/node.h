#ifndef NODE_H
#define NODE_H

#include "edge.h"

typedef struct node Node;

Node* init_node();

Node** init_node_vector(int n);

void add_edge(Node* node, int dest, double weight);

Edge* get_w(Node* node);

void set_w(Node* node, Edge* w);

void destroy_node(Node* node);

void destroy_node_vector(Node** node, int n_nodes);

#endif
            