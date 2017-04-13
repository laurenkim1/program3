#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include <string.h>


<<<<<<< HEAD

void print_array(int n, long nums[n]) {
    for (int i = 0; i < n; i++) {
        printf("%lu ", nums[i]);
    }
    printf("\n");
}

// max heap stuff
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

int extract_max(int *size, long heap[*size + 1]) {
    long max = heap[1];
    heap[1] = heap[*size];
    *size -= 1;
    max_heapify(*size, heap, 1);
    return max;
}

void insert(int *size, long heap[*size + 1], int num){
    *size += 1;
    heap[*size] = num;
    int x = *size;
    while (x != 1 && heap[x / 2] < heap[x]) {
        long tmp = heap[x];
        heap[x] = heap[x / 2];
        heap[x / 2] = tmp;
    }
}

// karmarkar-karp
long karmarkar_karp(int size, long prepartitioned[size]) {
    int *length = &(size);
    long *heap = calloc(size + 1, sizeof(long));
    memcpy(&heap[1], prepartitioned, size * sizeof(long));

    build_max_heap(size, heap);

    while (size > 1){
        long val1 = extract_max(length, heap);
        long val2 = extract_max(length, heap);
        insert(length, heap, labs(val1 - val2));
        size--;
    }
    return extract_max(length, heap);
}

// generates a random 64-bit integer
long rand64() {
    return ((long) rand() << 32) | rand();
}

// Returns the residue of a soln given a set of nums
long residue(int n, long soln[n], long nums[n]) {
    long res = 0;
    for (int i = 0; i < n; i++)
        res += soln[i] * nums[i];

    return labs(res);
}

long repeated_random(int n, long nums[n]) {
    long best_residue = LONG_MAX;
    long *soln = malloc(n * sizeof(long));
    for (int i = 0; i < MAX_ITER; i++) {
        for (int j = 0; j < n; j++)
            soln[j] = rand() % 2 ? -1 : 1;
        long res = residue(n, soln, nums);
        if (res < best_residue)
            best_residue = res;
    }
    free(soln);
    return best_residue;
}

long* rand_neighbor(int n, long soln[n]) {
    long *neighbor = malloc(n * sizeof(long));
    memcpy(neighbor, soln, n * sizeof(long));

    int i = rand() % n;
    int j = rand() % n;
    while (i == j)
        j = rand() % n;

    neighbor[i] *= -1;
    if (rand() % 2)
        neighbor[j] *= -1;

    return neighbor;
}

long hillclimb(int n, long nums[n]) {
=======
// functions for prepartitioned solution representation
long pp_repeated_random(int n, long nums[n]) {
>>>>>>> origin/master
    long *soln = malloc(n * sizeof(long));
    long* partition = calloc(n, sizeof(long));
    long best_residue = LONG_MAX;

    for (int i = 0; i < MAX_ITER; i++) {
        for (int j = 0; j < n; j++) {
            soln[j] = rand() % n;
            partition[j] = 0;
        }

        for (int j = 0; j < n; j++)
            partition[soln[i]] += nums[i];

        long res = karmarkar_karp(n, partition);
        if (res < best_residue)
            best_residue = res;
    }
    
    free(soln);
    free(partition);
    return best_residue;
}

long* pp_rand_neighbor(int n, long soln[n]) {
    long *neighbor = malloc(n * sizeof(long));
    memcpy(neighbor, soln, n * sizeof(long));
    int i = rand() % n;
    int j = rand() % n;
    while (neighbor[i] == j)
        j = rand() % n;

    neighbor[i] = j;
    return neighbor;
}

long pp_hillclimb(int n, long nums[n]) {
    long *soln = malloc(n * sizeof(long));
<<<<<<< HEAD
    for (iter = 0; iter < n; iter++){
        randsubset = rand() % SET_SIZE;
        soln[iter] = randsubset;
    }

    long* prepartitioned = malloc(n * sizeof(long));
    for (t = 0; t < n; t ++){
        prepartitioned[t] = 0;
    }

    for (t = 0; t < n; t ++){
        index = soln[t];
        prepartitioned[index] += nums[t];
=======
    long *partition = calloc(n, sizeof(long));
    for (int i = 0; i < n; i++) {
        soln[i] = rand() % n;
        partition[soln[i]] += nums[i];
>>>>>>> origin/master
    }
    long best_residue = karmarkar_karp(n, partition);

    for (int i = 0; i < MAX_ITER; i++) {
        long *neighbor = pp_rand_neighbor(n, soln);
<<<<<<< HEAD
        for (t = 0; t < n; t ++){
            prepartitioned[t] = 0;
        }

        for (t = 0; t < n; t ++){
            index = neighbor[t];
            prepartitioned[index] += nums[t];
        }
        long res = karmarkar_karp(n, prepartitioned);
=======
        for (int j = 0; j < n; j++)
            partition[j] = 0;

        for (int j = 0; j < n; j++)
            partition[neighbor[j]] += nums[j];

        long res = karmarkar_karp(n, partition);
>>>>>>> origin/master
        if (res < best_residue) {
            free(soln);
            best_residue = res;
            soln = neighbor;
        } else {
            free(neighbor);
        }
    }
    free(soln);
    free(partition);
    return best_residue;
}

long pp_annealing(int n, long nums[n]) {
    long *soln = malloc(n * sizeof(long));
<<<<<<< HEAD
    for (iter = 0; iter < n; iter++){
        randsubset = rand() % SET_SIZE;
        soln[iter] = randsubset;
    }

    long* prepartitioned = malloc(n * sizeof(long));
    for (t = 0; t < n; t ++){
        prepartitioned[t] = 0;
    }

    for (t = 0; t < n; t ++){
        index = soln[t];
        prepartitioned[index] += nums[t];
=======
    long *partition = calloc(n, sizeof(long));
    for (int i = 0; i < n; i++) {
        soln[i] = rand() % n;
        partition[soln[i]] += nums[i];
>>>>>>> origin/master
    }
    long soln_residue = karmarkar_karp(n, partition);
    long best_residue = soln_residue;

    for (int i = 0; i < MAX_ITER; i++) {
        long *neighbor = pp_rand_neighbor(n, soln);
<<<<<<< HEAD
        for (t = 0; t < n; t ++){
            prepartitioned[t] = 0;
        }

        for (t = 0; t < n; t ++){
            index = neighbor[t];
            prepartitioned[index] += nums[t];
        }
        long res = karmarkar_karp(n, prepartitioned);
=======
        for (int j = 0; j < n; j++)
            partition[j] = 0;

        for (int j = 0; j < n; j++)
            partition[neighbor[j]] += nums[j];
>>>>>>> origin/master

        long res = karmarkar_karp(n, partition);
        if (res < best_residue) {
            free(soln);
            best_residue = res;
            soln = neighbor;
        } else {
            double prob = exp(-(res - soln_residue) / T(i));
            if ((double) rand()/INT_MAX > prob) {
                free(soln);
                soln_residue = res;
                soln = neighbor;
            } else {
                free(neighbor);
            }
        }
    }
    free(soln);
    free(partition);
    return best_residue;
}


int main (int argc, char *argv[]) {
    // input validation
    if (argc != 2) {
        printf("Usage: kk inputfile\n");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Error: unable to open file %s\n", argv[1]);
        return 1;
    }

    // reading the file into memory
    long nums[SET_SIZE] = {};
    char buffer[14];
    int i = 0;
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        nums[i++] = atol(buffer);
    }
    fclose(fp);

    // actual testing
    srand(time(NULL));

    clock_t start, end;

    // prepartitioned solution representation trials
    printf("Prepartitioned: \n");
    start = clock();
    printf("Repeated Random:    %8lu | ", pp_repeated_random(SET_SIZE, nums));
    end = clock();
    printf("%.3f ms\n", 1000 * (double) (end - start)/CLOCKS_PER_SEC);

    start = clock();
    printf("Hill Climbing:      %8lu | ", pp_hillclimb(SET_SIZE, nums));
    end = clock();
    printf("%.3f ms\n", 1000 * (double) (end - start)/CLOCKS_PER_SEC);

    start = clock();
    printf("Simulated Annealing:%8lu | ", pp_annealing(SET_SIZE, nums));
    end = clock();
    printf("%.3f ms\n", 1000 * (double) (end - start)/CLOCKS_PER_SEC);
}
