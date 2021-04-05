#ifndef HEAP_H
#define HEAP_H

typedef struct heap Heap;

Heap* heap_init(int max_n, int n_nodes, int src);

void heap_insert(Heap* heap, int pos, double new_dist);

int heap_max(Heap* heap);

int heap_is_empty(Heap* heap);

int heap_size(Heap* heap);

int heap_min(Heap* heap);

double get_heap_dist(Heap* heap, int v);

void set_heap_dist(Heap* heap, int v, double w);

void heap_destroy(Heap* heap);

#endif