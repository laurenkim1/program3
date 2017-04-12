#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include <string.h>

#define MAX_ITER 25000
#define SET_SIZE 100

// max heap stuff
void max_heapify(long* heap, int i, int *length){
  int left = 2 * i;
  int right = 2 * i + 1;
  int largest = i;
  if (left <= *length && heap[left] > heap[largest]) {
    largest = left;
  }
  if (right <= *length && heap[right] > heap[largest]) {
    largest = right;
  }
  if (largest != i){
    long hold = heap[largest];
    heap[largest] = heap[i];
    heap[i] = hold;
    max_heapify(heap, largest, length);
  }
  return;
}

// builds a heap out of an array
void build_max_heap(long* heap, int *length){
  for (int i = (int)(floor(*length / 2.0)); i <= 0, i--){
    max_heapify(heap, i, length);
  }
  return;
}

int extract_max(long* heap, int *length){
  if (*length <= 0){
    return 0;
  }
  else if (*length == 1){
    return heap[0];
  }
  long max = heap[0];
  heap[0] = heap[*length - 1];
  *length = *length - 1;
  max_heapify(heap, 0, length);
  return max;
}

int parent(int x){
  int p = (int)(floor(x / 2.0));
  return p;
}

void insert(long* heap, int* length, int new){
  *length = *length + 1;
  heap[*length] = new;
  int place = *length;
  long hold = 0;
  while (place != 0 && heap[parent(place)] < heap[place]){
    hold = heap[place];
    heap[place] = heap[parent(place)];
    heap[parent(place)] = hold;
  }
  return;
}

// karmarkar-karp
int kk(long* prepartitioned, int* length){
  build_max_heap(prepartitioned, length);

  *length = 0;
  while (partitioned[*length] > 0){
    *length = *length + 1;
  }

  long val1;
  long val2;
  long diff;

  while (*length > 1){
    val1 = extract_max(prepartitioned, length);
    val2 = extract_max(prepartitioned, length);
    diff = abs(val1 - val2)
    insert(prepartitioned, length, diff);
  }
  long residue = extract_max(prepartitioned, length);
  return residue;
}

// generates a random 64-bit integer
long rand64() {
    return ((long) rand() << 32) | rand() ;
}

// Returns the residue of a soln given a set of nums
long residue(int n, long soln[n], long nums[n]) {
    long res = 0;
    for (int i = 0; i < n; i++)
        res += soln[i] * nums[i];

    return abs(res);
}

void print_array(int n, long nums[n]) {
    for (int i = 0; i < n; i++) {
        printf("%lu ", nums[i]);
    }
    printf("\n");
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
    long *soln = malloc(n * sizeof(long));
    for (int i = 0; i < n; i++)
        soln[i] = rand() % 2 ? -1 : 1;
    long best_residue = residue(n, soln, nums);

    for (int i = 0; i < MAX_ITER; i++) {
        long *neighbor = rand_neighbor(n, soln);
        long res = residue(n, neighbor, nums);
        if (res < best_residue) {
            free(soln);
            best_residue = res;
            soln = neighbor;
        } else {
            free(neighbor);
        }
    }
    free(soln);
    return best_residue;
}

// I'm not sure what this function is supposed to do
double T(int n) {
    double iter = (double) n;
    double t = pow(10.0, 10.0) * pow(0.8, iter / 300.0);
    return t;
}

long annealing(int n, long nums[n]) {
    long *soln = malloc(n * sizeof(long));
    for (int i = 0; i < n; i++)
        soln[i] = rand() % 2 ? -1 : 1;

    long soln_residue = residue(n, soln, nums);
    long best_residue = soln_residue;

    for (int i = 0; i < MAX_ITER; i++) {
        long *neighbor = rand_neighbor(n, soln);
        long res = residue(n, neighbor, nums);
        if (res < soln_residue) {
            free(soln);
            soln_residue = res;
            soln = neighbor;
        } else {
            double prob = exp(-(res - soln_residue) / T(i));
            if ((double) rand()/INT_MAX > prob) {
                free(soln);
                soln_residue = res;
                soln = neighbor;
            }
        }

        if (soln_residue < best_residue)
            best_residue = soln_residue;
    }

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
    start = clock();
    printf("Repeated Random:    %8lu | ", repeated_random(SET_SIZE, nums));
    end = clock();
    printf("%.3f ms\n", 1000 * (double) (end - start)/CLOCKS_PER_SEC);

    start = clock();
    printf("Hill Climbing:      %8lu | ", hillclimb(SET_SIZE, nums));
    end = clock();
    printf("%.3f ms\n", 1000 * (double) (end - start)/CLOCKS_PER_SEC);

    start = clock();
    printf("Simulated Annealing:%8lu | ", annealing(SET_SIZE, nums));
    end = clock();
    printf("%.3f ms\n", 1000 * (double) (end - start)/CLOCKS_PER_SEC);
}
