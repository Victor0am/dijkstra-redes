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
    int src;
} Pair;

struct heap {
    int n;
    int max_n;
    Pair **pq;
};

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