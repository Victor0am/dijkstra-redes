#include "./heap.h"

#include <float.h>
#include <stdio.h>
#include <stdlib.h>

#include "./edge.h"

/**
 * @param n number of edges in keys
 * @param max_n max size of priority queue
 * @param dist array of distances from source to other nodes
 * @param keys priority queue, where each int is a node index
 */

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

/*
Heap *heap_init(int max_n) {
    Heap *h = (Heap *)malloc(sizeof(Heap));
    h->n = 0;
    h->max_n = max_n;
    h->pq = (Pair **)malloc(max_n * sizeof(Pair *));

    return h;
}

static void heapify_bottom_top(Heap *h, int index) {
    Pair *temp;
    int parent_node = (index - 1) / 2;

    if (h->pq[parent_node]->dist > h->pq[index]->dist) {
        temp = h->pq[parent_node];
        h->pq[parent_node] = h->pq[index];
        h->pq[index] = temp;
        heapify_bottom_top(h, parent_node);
    }
}

static void heapify_top_bottom(Heap *h, int parent_node) {
    int left = parent_node * 2 + 1;
    int right = parent_node * 2 + 2;
    int min;
    Pair *temp;

    if (left >= h->n || left < 0)
        left = -1;
    if (right >= h->n || right < 0)
        right = -1;

    if (left != -1 && h->pq[left]->dist < h->pq[parent_node]->dist)
        min = left;
    else
        min = parent_node;
    if (right != -1 && h->pq[right]->dist < h->pq[min]->dist)
        min = right;

    if (min != parent_node) {
        temp = h->pq[min];
        h->pq[min] = h->pq[parent_node];
        h->pq[parent_node] = temp;

        heapify_top_bottom(h, min);
    }
}

void heap_insert(Heap *h, int src, double dist) {
    if (h->n < h->max_n) {
        Pair *pair = (Pair *)malloc(sizeof(Pair));
        pair->src = src;
        pair->dist = dist;

        h->pq[h->n] = pair;
        heapify_bottom_top(h, h->n);
        h->n++;
    }
}

int heap_is_empty(Heap *heap) {
    return heap->n == 0;
}

int heap_min(Heap *h) {
    Pair *pop;
    pop = h->pq[0];
    h->pq[0] = h->pq[h->n - 1];
    h->n--;

    int src = pop->src;
    free(pop);
    heapify_top_bottom(h, 0);
    return src;
}

static void destroy_pairs(Heap *h) {
    for (int i = 0; i < h->n; i++) {
        free(h->pq[i]);
    }
    free(h->pq);
}

void heap_destroy(Heap *heap) {
    destroy_pairs(heap);
    free(heap);
}
*/