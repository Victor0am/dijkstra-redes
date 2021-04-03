#include "./node.h"

#include <stdlib.h>

#include "./edge.c"

struct node {
    Edge* w;
};

Node* init_node() {
    // initializes empty node
    Node* new_node = (Node*)malloc(sizeof(Node));
    return new_node;
}

Node** init_node_vector(int n) {
    Node** nodes = (Node**)malloc(sizeof(Node*) * n);
    for (int i = 0; i < n; i++) {
        nodes[i] = init_node();
    }

    return nodes;
}

Edge* get_w(Node* node) {
    return node->w;
}

void set_w(Node* node, Edge* w) {
    node->w = w;
}

void destroy_node(Node* node) {
    destroy_edge_vector(node->w);
}

void destroy_node_vector(Node** node, int n_nodes) {
    for (int i = 0; i < n_nodes; i++) {
        destroy_node(node[i]);
    }
}
