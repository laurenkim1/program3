// preserve the heap invariant
void max_heapify(int size, long heap[size + 1], int n){
    int left = 2 * n;
    int right = 2 * n + 1;
    int largest = n;
    if (left <= size && heap[left] > heap[n])
        largest = left;
    if (right <= size && heap[right] > heap[largest])
        largest = right;

    if (largest != n) {
        long tmp = heap[largest];
        heap[largest] = heap[n];
        heap[n] = tmp;
        max_heapify(size, heap, largest);
    }
}

// builds a heap out of an array
void build_max_heap(int size, long heap[size + 1]) {
    for (int i = size / 2; i > 0; i--)
        max_heapify(size, heap, i);
}

// remove an element from a heap
long extract_max(int *size, long heap[*size + 1]) {
    long max = heap[1];
    heap[1] = heap[*size];
    *size -= 1;
    max_heapify(*size, heap, 1);
    return max;
}

// insert an element into a heap
void insert(int *size, long heap[*size + 1], long num){
    *size += 1;
    heap[*size] = num;
    int x = *size;
    while (x != 1 && heap[x / 2] < heap[x]) {
        long tmp = heap[x];
        heap[x] = heap[x / 2];
        heap[x / 2] = tmp;
        x /= 2;
    }
}