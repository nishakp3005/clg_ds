#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *array;
    int size;
    int capacity;
} MaxHeap;

MaxHeap *initHeap(int capacity) {
    MaxHeap *heap = (MaxHeap *)malloc(sizeof(MaxHeap));
    heap->array = (int *)malloc(sizeof(int) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void destroyHeap(MaxHeap *heap) {
    free(heap->array);
    free(heap);
}

void heapify(MaxHeap *heap, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->size && heap->array[left] > heap->array[largest]) {
        largest = left;
    }

    if (right < heap->size && heap->array[right] > heap->array[largest]) {
        largest = right;
    }

    if (largest != i) {
        // Swap the values
        int temp = heap->array[i];
        heap->array[i] = heap->array[largest];
        heap->array[largest] = temp;

        // Recursively heapify the affected sub-tree
        heapify(heap, largest);
    }
}

void insert(MaxHeap *heap, int value) {
    if (heap->size == heap->capacity) {
        printf("Heap is full. Cannot insert.\n");
        return;
    }

    // Insert the new element at the end
    int i = heap->size;
    heap->array[i] = value;
    heap->size++;

    // Fix the max-heap property
    while (i > 0 && heap->array[(i - 1) / 2] < heap->array[i]) {
        // Swap the values
        int temp = heap->array[i];
        heap->array[i] = heap->array[(i - 1) / 2];
        heap->array[(i - 1) / 2] = temp;

        // Move to the parent index
        i = (i - 1) / 2;
    }
}

void peek_max(MaxHeap *heap) {
    if (heap->size > 0) {
        printf("Maximum element: %d\n", heap->array[0]);
    } else {
        printf("Heap is empty.\n");
    }
}

int extractMax(MaxHeap *heap) {
    if (heap->size <= 0) {
        printf("Heap is empty. Cannot extract.\n");
        return -1; // Assuming -1 represents an invalid value for simplicity
    }

    int max = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;

    // Restore the max-heap property
    heapify(heap, 0);

    return max;
}

void display_heap(MaxHeap *heap, int stop_idx) {
    printf("Max-Heap: ");
    for (int i = 0; i <= stop_idx && i < heap->size; i++) {
        printf("%d ", heap->array[i]);
    }
    printf("\n");
} 

MaxHeap *constructHeap(int *arr, int arr_length) {
    MaxHeap *heap = initHeap(arr_length);

    // Copy the array elements into the max-heap array
    for (int i = 0; i < arr_length; i++) {
        heap->array[i] = arr[i];
    }

    // Build the max-heap using Floyd's method
    for (int i = (arr_length - 1) / 2; i >= 0; i--) {
        heapify(heap, i);
    }

    return heap;
}

void heapSort_ascending(MaxHeap *heap) {
    // Build max-heap from the array
    for (int i = (heap->size - 1) / 2; i >= 0; i--) {
        heapify(heap, i);
    }

    // Extract elements one by one and build sorted array
    for (int i = heap->size - 1; i > 0; i--) {
        // Swap root (maximum element) with the last element
        int temp = heap->array[0];
        heap->array[0] = heap->array[i];
        heap->array[i] = temp;

        // Heapify the reduced heap
        heapify(heap, 0);
    }
}

int main() {
    // Example usage of the max-heap functions
    MaxHeap *heap = initHeap(10);

    insert(heap, 4);
    insert(heap, 10);
    insert(heap, 8);
    insert(heap, 5);
    insert(heap, 1);

    display_heap(heap, heap->size - 1);

    printf("Extracted Max: %d\n", extractMax(heap));

    display_heap(heap, heap->size - 1);

    peek_max(heap);

    int arr[] = {12, 3, 7, 1, 8, 5};
    int arr_length = sizeof(arr) / sizeof(arr[0]);

    MaxHeap *constructedHeap = constructHeap(arr, arr_length);

    display_heap(constructedHeap, constructedHeap->size - 1);

    heapSort_ascending(constructedHeap);

    display_heap(constructedHeap, constructedHeap->size - 1);

    destroyHeap(heap);
    destroyHeap(constructedHeap);

    return 0;
}
