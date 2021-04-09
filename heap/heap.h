

typedef struct heap Heap;

// Argument is maximum expected number of items.
Heap* heap_init(int size);  // Creates an empty priority queue.

void heap_insert(Heap* heap, int item);  // Inserts an item in the priority queue.

// Removes and returns the largest item.
int heap_delmax();  // Dual op delmin also possible.

int heap_max();  // Returns the largest item. Dual: min.

int heap_empty();  // Tests if the queue is empty.

int heap_size();  // Number of entries in the priority queue.

void heap_finish();  // Cleans up the queue.