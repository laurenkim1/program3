#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct max_heap {
    int size;
    int length;
    long *nums;
}
max_heap;

// preserve the heap invariant
void max_heapify(max_heap *heap, int n){
    int left = 2 * n;
    int right = 2 * n + 1;
    int largest = n;
    if (left <= heap->size && heap->nums[left] > heap->nums[n])
        largest = left;
    if (right <= heap->size && heap->nums[right] > heap->nums[largest])
        largest = right;

    if (largest != n) {
        long tmp = heap->nums[largest];
        heap->nums[largest] = heap->nums[n];
        heap->nums[n] = tmp;
        max_heapify(heap, largest);
    }
}

// builds a heap out of an array
max_heap* build_max_heap(int size, long nums[size]) {
    max_heap *heap = malloc(sizeof(max_heap));
    heap->size = size;
    heap->length = size + 1;
    heap->nums = malloc((size + 1) * sizeof(long));
    memcpy(&heap->nums[1], nums, size * sizeof(long));
    for (int i = size / 2; i > 0; i--)
        max_heapify(heap, i);

    return heap;
}

// extract the maximum element from a heap
long extract_max(max_heap *heap) {
    long max = heap->nums[1];
    heap->nums[1] = heap->nums[heap->size];
    heap->size -= 1;
    max_heapify(heap, 1);
    return max;
}

// insert an element into a heap
void insert(max_heap *heap, int num){
    heap->size += 1;
    heap->nums[heap->size] = num;
    int x = heap->size;
    while (x != 1 && heap->nums[x / 2] < heap->nums[x]) {
        long tmp = heap->nums[x];
        heap->nums[x] = heap->nums[x / 2];
        heap->nums[x / 2] = tmp;
    }
}

int main(void) {
    long nums[] = {1, 2, 10, 4, 5, 6, 7, 8, 9, 3};
    max_heap *heap = build_max_heap(10, nums);


    while (heap->size > 1) {
        printf("%lu\n", extract_max(heap));
    }

    printf("Size: %d\n\n", heap->size);
    for (int j = 11; j <= 20; j++) {
        insert(heap, j);
    }

    while (heap->size > 0) {
        printf("%lu\n", extract_max(heap));
    }
}