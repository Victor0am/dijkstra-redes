#include "./heap.h"

struct heap {
    int n;
    int max_n;
    int* pq; //priority queue
};

Heap* heap_init(int max_n) {
    Heap* new = (Heap*) malloc (sizeof(Heap));
    new->n = 0;
    new->max_n = max_n;

    for (int i = 0; i < max_n; i++) 
        new->pq[i] = -1;

    return new;
}

void heap_insert() {

}

int heap_is_empty(Heap* heap) {
    return heap->n == 0;
}

int heap_size(Heap* heap) {
    return heap->n;
}

