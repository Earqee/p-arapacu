#ifndef HEAP_AHRT
#define HEAP_AHRT

/* Defining the abstract data type HEAP */
typedef struct HEAP {
    GENERIC *array;
    INTEGER size;
} HEAP;

/* Allocates a HEAP pointer. Allocates a Generic pointer to an array of size
MAX_HEAP_SIZE. Sets the initial heap size equals to zero. Returns the HEAP 
allocated pointer. */
GENERIC HEAP_Create() {
    HEAP *new_heap = (HEAP*) malloc(sizeof(HEAP));
    new_heap->array = (GENERIC*) calloc(MAX_HEAP_SIZE, sizeof(GENERIC));
    new_heap->size = 0;
    return new_heap;
}

/* Recieves an INTEGER index and returns its parent index in the heap. */
INTEGER HEAP_Get_Parent(INTEGER index) {
    return (index >> 1);
}

/* Recieves an INTEGER index and returns its left child index in the heap. */
INTEGER HEAP_Get_Left_Child(INTEGER index) {
    return (index << 1);
}

/* Recieves an INTEGER index and returns its right child index in the heap. */
INTEGER HEAP_Get_Right_Child(INTEGER index) {
    return ((index << 1) + 1);
}

/* Recieves a HEAP pointer and two INTEGERS: first_index and second_index.
Exchanges the content of the two nodes in the heap, given their indexes. */
void HEAP_Swap(HEAP *heap, INTEGER first_index, INTEGER second_index) {
    GENERIC aux = heap->array[first_index];
    heap->array[first_index] = heap->array[second_index];
    heap->array[second_index] = aux;
    return;
}

/* Recieves a HEAP pointer, a GENERIC data and a boolean pointer to function, Lambda.
Enqueues the given data in the heap, utilizing as a comparision function to maintain the
heap property the Lambda function. */
void HEAP_Enqueue(HEAP *heap, GENERIC data, bool (*Lambda)()) {
    heap->array[++heap->size] = data;
    INTEGER current = heap->size;
    INTEGER parent = HEAP_Get_Parent(current);

    while(parent >= 1 && Lambda(heap->array[current], heap->array[parent])) {
        HEAP_Swap(heap, current, parent);
        current = parent;
        parent = HEAP_Get_Parent(current);
    }
    return;
}

/* Recieves a HEAP pointer, an INTEGER index and a boolean pointer to function, Lambda.
Applies the boolean function Lambda to the node of given index and both of its childs to 
maintain the heap property (heapify). Recursively heapifies the rest of the heap. */
void HEAP_Heapify(HEAP *heap, INTEGER index, bool (*Lambda)()) {
    INTEGER least = index;
    INTEGER left = HEAP_Get_Left_Child(index);
    INTEGER right = HEAP_Get_Right_Child(index);

    if(left <= heap->size) {
        if(Lambda(heap->array[least], heap->array[left])) {
            least = left;
        }
    }
    if(right <= heap->size) {
        if(Lambda(heap->array[least], heap->array[right])) {
            least = right;
        }
    }
    if(least != index) {
        HEAP_Swap(heap, index, least);
        HEAP_Heapify(heap, least, Lambda);
    }
    return;
}

/* Recieves a HEAP pointer and a boolean pointer to function, Lambda. Removes the
first node of the heap and then uses Lambda to applie heapify in the first node, 
preserving the heap property. */
GENERIC HEAP_Dequeue(HEAP *heap, bool (*Lambda)()) {
    GENERIC save_first = heap->array[1];
    HEAP_Swap(heap, 1, heap->size--);
    HEAP_Heapify(heap, 1, Lambda);
    return save_first;
}

#endif