#include "./heap.h"

#include <float.h>
#include <stdio.h>
#include <stdlib.h>

#include "./edge.h"

/**
 * @param n number of edges in keys
 * @param max_n max size of priority queue
 * @param dist_to array of distances from source to other nodes
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
    Heap *h = (Heap *)malloc(sizeof(Heap));  //one is number of heap

    //check if memory allocation is fails
    if (h == NULL) {
        printf("Memory Error!");
        return NULL;
    }
    h->n = 0;
    h->max_n = max_n;
    h->pq = (Pair **)malloc(max_n * sizeof(Pair *));  //size in bytes

    return h;
}

void heapify_bottom_top(Heap *h, int index) {
    Pair *temp;
    int parent_node = (index - 1) / 2;

    if (h->pq[parent_node]->dist > h->pq[index]->dist) {
        //swap and recursive call
        temp = h->pq[parent_node];
        h->pq[parent_node] = h->pq[index];
        h->pq[index] = temp;
        heapify_bottom_top(h, parent_node);
    }
}

void heapify_top_bottom(Heap *h, int parent_node) {
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

        // recursive  call
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
    if (heap_is_empty(h)) {
        printf("\n__Heap is Empty__\n");
        return -1;
    }
    // replace first node by last and delete last
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

/*
static double get_dist(Heap* heap, int key) {
    return heap->dist_to[key];
}

Heap* heap_init(int max_n, int n_nodes, int src) {
    Heap* new = (Heap*)malloc(sizeof(Heap));
    double* dist_to = (double*)malloc(sizeof(double) * (n_nodes));
    new->keys = (int*)malloc(sizeof(int) * (n_nodes + 1));

    for (int i = 0; i < n_nodes; i++) {
        dist_to[i] = DBL_MAX;
    }

    new->dist_to = dist_to;
    new->n = 0;
    new->max_n = max_n;

    return new;
}

static void exchange(Heap* heap, int j, int k) {
    int aux_edge;
    aux_edge = heap->keys[j];
    heap->keys[j] = heap->keys[k];
    heap->keys[k] = aux_edge;
}

static void fix_up(Heap* heap, int k) {
    while (k > 1 && (get_dist(heap, k / 2) < get_dist(heap, k))) {
        exchange(heap, k, k / 2);
        k = k / 2;
    }
}

static void fix_down(Heap* heap, int sz, int k) {
    int aux;

    while (2 * k <= sz) {
        aux = 2 * k;

        if (aux < sz && get_dist(heap, aux + 1) < get_dist(heap, aux))
            aux++;

        if (get_dist(heap, aux) <= get_dist(heap, k))
            break;

        exchange(heap, k, aux);
        k = aux;
    }
}

void heap_insert(Heap* heap, int pos, double new_dist) {
    heap->n++;
    heap->keys[heap->n] = pos;
    heap->dist_to[pos] = new_dist;
    fix_up(heap, heap->n);
}

int heap_max(Heap* heap) {
    return heap->max_n;
}

int heap_is_empty(Heap* heap) {
    return heap->n == 0;
}

int heap_size(Heap* heap) {
    return heap->n;
}

int heap_min(Heap* heap) {
    int min = heap->keys[1];
    exchange(heap, 1, heap->n);
    heap->n--;
    fix_down(heap, heap->n, 1);
    return min;
}

double get_heap_dist(Heap* heap, int v) {
    return heap->dist_to[v];
}

int heap_min_dist(Heap* heap) {
    return heap->dist_to[heap->keys[1]];
}

void set_heap_dist(Heap* heap, int v, double w) {
    heap->dist_to[v] = w;
}

void heap_destroy(Heap* heap) {
    free(heap->dist_to);
    free(heap->keys);
    free(heap);
}

*/