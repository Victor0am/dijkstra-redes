#include <stdio.h>

#include "heap.h"

int main() {
    int i;
    Heap *heap = heap_init(9);  //Min Heap

    if (heap == NULL) {
        printf("__Memory Issue____\n");
        return -1;
    }

    heap_insert(heap, 4);
    heap_insert(heap, 7);
    heap_insert(heap, 5);
    heap_insert(heap, 6);
    heap_insert(heap, 8);
    heap_insert(heap, 9);
    heap_insert(heap, 3);
    heap_insert(heap, 1);
    heap_insert(heap, 2);

    for (i = 9; i >= 0; i--) {
        printf(" Pop Minima : %d\n", heap_max(heap));
    }
    return 0;
}