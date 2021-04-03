#ifndef NODE_H
#define NODE_H

typedef struct node Node;

#include "node.h"

Node* init_node();

Node** init_node_vector(int n);

Edge* get_w(Node* node);

void set_w(Node* node, Edge* w);

void destroy_node(Node* node);

void destroy_node_vector(Node** node, int n_nodes);

#endif