#include "./heap.h"

#include <float.h>
#include <stdio.h>
#include <stdlib.h>

#include "./edge.h"

// dist: peso
// src: identificado do item
typedef struct pair {
    double dist;
    int key;
} Pair;

#define key(A) (A->key)                 // retorna identificador do nó
#define dist(A) (A->dist)               // retorna valor do nó
#define more(A, B) (dist(A) > dist(B))  // compara nós, por valor
#define exch(A, B)   \
    {                \
        Pair *t = A; \
        A = B;       \
        B = t;       \
    }  // troca dois nós
struct heap {
    int n;
    int *map;
    Pair **pq;
};

static void swap(Pair **pq, int *map, int i, int j) {
    exch(pq[i], pq[j]);
    map[key(pq[i])] = i;
    map[key(pq[j])] = j;
}

void fix_up(Pair **pq, int *map, int k) {
    while (k > 1 && more(pq[k / 2], pq[k])) {
        swap(pq, map, k, k / 2);
        k = k / 2;
    }
}

void fix_down(Pair **pq, int *map, int sz, int k) {
    while (2 * k <= sz) {
        int j = 2 * k;
        if (j < sz && more(pq[j], pq[j + 1])) {
            j++;
        }
        if (!more(pq[k], pq[j])) {
            break;
        }
        swap(pq, map, k, j);
        k = j;
    }
}

Heap *heap_init(int maxN) {
    Heap *new_heap = (Heap *)malloc(sizeof(Heap));
    new_heap->pq = (Pair **)malloc((maxN + 1) * sizeof(Pair *));
    new_heap->map = (int *)malloc((maxN + 1) * sizeof(int));
    new_heap->n = 0;
}

void heap_insert(Heap *heap, int key, double dist) {
    Pair *new_pair = (Pair *)malloc(sizeof(Pair));
    new_pair->key = key;
    new_pair->dist = dist;
    heap->n++;
    heap->pq[heap->n] = new_pair;
    heap->map[key(new_pair)] = heap->n;
    fix_up(heap->pq, heap->map, heap->n);
}

void heap_delmin(Heap *heap) {
    Pair *min = heap->pq[1];
    swap(heap->pq, heap->map, 1, heap->n);
    heap->n--;
    fix_down(heap->pq, heap->map, heap->n, 1);
    free(min);
}

int heap_min(Heap *heap) {
    return heap->pq[1]->key;
}

void heap_decrease_key(Heap *heap, int id, double value) {
    int i = heap->map[id];
    dist(heap->pq[i]) = value;
    fix_up(heap->pq, heap->map, i);
}

int heap_is_empty(Heap *heap) {
    return heap->n == 0;
}

static void destroy_pq(Heap *heap) {
    for (int i = 1; i < heap->n; i++) {
        free(heap->pq[i]);
    }
}

void heap_destroy(Heap *heap) {
    destroy_pq(heap);
    free(heap->map);
    free(heap->pq);
    free(heap);
}
