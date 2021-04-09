#ifndef HEAP_H
#define HEAP_H

typedef struct heap Heap;

Heap* heap_init(int max_n);

void heap_insert(Heap* heap, int pos, double new_dist);

int heap_is_empty(Heap* heap);

int heap_min(Heap* heap);

void heap_destroy(Heap* heap);

#endif