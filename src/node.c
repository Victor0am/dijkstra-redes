#include "./node.h"

#include <stdio.h>
#include <stdlib.h>

#include "./edge.h"

// w - lista de arestas
struct node {
    Edge* w;
};

Node* init_node() {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->w = NULL;
    return new_node;
}

Node** init_node_vector(int n) {
    Node** nodes = (Node**)malloc(sizeof(Node*) * n);
    for (int i = 0; i < n; i++) {
        nodes[i] = init_node();
    }

    return nodes;
}

void add_edge(Node* node, int dest, double weight) {
    Edge* new_edge = init_edge_list(dest, weight);

    if (node->w == NULL) {
        node->w = new_edge;
    } else {
        set_next(new_edge, node->w);
        node->w = new_edge;
    }
}

Edge* get_w(Node* node) {
    return node->w;
}

void destroy_node(Node* node) {
    destroy_edge_list(node->w);
    free(node);
}

void destroy_node_vector(Node** node, int n_nodes) {
    for (int i = 0; i < n_nodes; i++) {
        destroy_node(node[i]);
    }

    free(node);
}
