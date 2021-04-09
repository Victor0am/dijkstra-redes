#include "heap.h"

#include <stdlib.h>

struct heap {
    int *pq;
    int N;
    int max_tam;
};

Heap *heap_init(int size) {
    Heap *heap = (Heap *)malloc(sizeof(Heap));

    heap->pq = (int *)malloc(sizeof(int) * (size + 1));
    heap->max_tam = size;
    heap->N = 0;

    return heap;
}

int greater(int x, int y) {
    return x > y;
}

void fix_up(int *a, int k) {  // swim up
    while (k > 1 && greater(a[k / 2], a[k])) {
        int aux = a[k];
        a[k] = a[k / 2];
        a[k / 2] = a[k];
        k = k / 2;
    }
}

void fix_down(int *a, int sz, int k) {
    while (2 * k <= sz) {
        int j = 2 * k;
        if (j < sz && greater(a[j], a[j + 1])) {
            j++;
        }
        if (!greater(a[k], a[j])) {
            break;
        }
        int aux = a[k];
        a[k] = a[j];
        a[j] = a[k];
        k = j;
    }
}

void heap_insert(Heap *heap, int v) {
    if (heap->N < heap->max_tam) {
        heap->N++;
        heap->pq[heap->N] = v;
        fix_up(heap->pq, heap->N);
    }
}

int heap_delmax(Heap *heap) {
    int max = heap->pq[1];
    int aux = heap->pq[1];
    heap->pq[1] = heap->pq[heap->N];
    heap->pq[heap->N] = heap->pq[1];
    heap->N--;
    fix_down(heap->pq, heap->N, 1);
    return max;
}