#include <stdio.h>
#include <stdlib.h>
#include "./heap.h"
#include "./edge.h"
#include <float.h>

struct heap {
    int n; // number of edges in keys
    int max_n; // max size of the priority queue 
    double* dist_to; // array of distances from source to other nodes
    int* keys; // priority queue, where each int is a node index
};

static double get_dist(Heap* heap, int key) {
    return heap->dist_to[key];
}

Heap* heap_init(int max_n, int n_nodes, int src) {
    Heap* new = (Heap*) malloc (sizeof(Heap));
    double* dist_to = (double*) malloc (sizeof(double)*(n_nodes));
    new->keys = (int*) malloc(sizeof(int)*(n_nodes+1));
    
    for(int i = 0; i < n_nodes; i++){
            dist_to[i] = DBL_MAX;        
    }
    
    new->dist_to = dist_to;
    new->n = 0;
    new->max_n = max_n;

    return new;
}

void heap_insert(Heap* heap, int pos, double new_dist) {
    heap->n++;
    heap->keys[heap->n] = pos;
    heap->dist_to[pos] = new_dist; 
    fix_up(heap, heap->n);
    // for(int i = 0; i < heap->n; i++){
    //     printf("%d", heap->keys[i]);
    // }
}

void exchange (Heap* heap, int j, int k) {
    int aux_edge;
    aux_edge = heap->keys[j];
    heap->keys[j] = heap->keys[k];
    heap->keys[k] = aux_edge;    
}

void fix_up(Heap* heap, int k) {
    // swim up()
    while (k > 1 && (get_dist(heap, k/2) < get_dist(heap, k))) {
        exchange(heap, k, k/2); 
        k = k/2;
    }
    /*
    while (k > 1 && less(a[k/2], a[k])) {
        exch(a[k], a[k/2]);
        k = k/2;
    }
    */
}

void fix_down(Heap* heap, int sz, int k) {
    int aux;

    while (2 * k <= sz) {
        aux = 2*k;
       
        if (aux < sz && get_dist(heap, aux+1) < get_dist(heap, aux)) 
            aux++;
        
        if (get_dist(heap, aux) <= get_dist(heap, k))
            break;

        exchange(heap, k, aux);
        k = aux;
    }
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
    /*
    Item max = pq[1];
    exch(pq[1], pq[N]);
    N--;
    fix_down(pq, N, 1);
    return max;
    */
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