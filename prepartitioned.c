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
int kk(long* prepartitioned){
    int* length = SET_SIZE;
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

long repeated_random(int n, long* nums){
    int iter = 0;
    int t = 0;
    int index = 0;

    long *soln = malloc(n * sizeof(long));
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
    }

    long best_residue = kk(prepartitioned);

    for (int k = 0; k < MAX_ITER; k++){
        for (iter = 0; iter < n; iter++){
            randsubset = rand() % SET_SIZE;
            soln[iter] = randsubset;
        }
        for (t = 0; t < n; t ++){
            prepartitioned[t] = 0;
        }

        for (t = 0; t < n; t ++){
            index = soln[t];
            prepartitioned[index] += nums[t];
        }
        long res = kk(prepartitioned);
        if (res < best_residue)
            best_residue = res;
    }
    free(soln);
    free(prepartitioned);
    return best_residue;
}

long* rand_neighbor(int n, long soln[n]) {
    long *neighbor = malloc(n * sizeof(long));
    memcpy(neighbor, soln, n * sizeof(long));

    do {
      i = rand() % SET_SIZE;
      j = rand() % SET_SIZE;
    } while (soln[i] == j);

    neighbor[i] = j;

    return neighbor;
}

long hillclimb(int n, long nums[n]) {
    int iter = 0;
    int t = 0;
    int index = 0;

    long *soln = malloc(n * sizeof(long));
    for (iter = 0; iter < 100; iter++){
        randsubset = rand() % SET_SIZE;
        soln[iter] = randsubset;
    }

    long* prepartitioned = malloc(100 * sizeof(long));
    for (t = 0; t < 100; t ++){
        prepartitioned[t] = 0;
    }

    for (t = 0; t < 100; t ++){
        index = soln[t];
        prepartitioned[index] += nums[t];
    }

    long best_residue = kk(prepartitioned);

    long i = 0;
    long j = 0;
    long last = 0;
    for (int k = 0; k < MAX_ITER; k++) {
        long *neighbor = rand_neighbor(n, soln);
        for (t = 0; t < 100; t ++){
            prepartitioned[t] = 0;
        }

        for (t = 0; t < 100; t ++){
            index = neighbor[t];
            prepartitioned[index] += nums[t];
        }
        long res = kk(prepartitioned);
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

int main (void) {
  // seeding random number generator once
  time_t seconds;
  time(&seconds);
  srand((unsigned int) seconds);

  FILE *input = fopen(argv[3], "r");
    if (input == NULL){
        fprintf(stderr, "Could not open file");
        exit(1);
    }

  char line[64];

  int iter;
  int new;
  int randsubset;

  int* nums = malloc(100 * sizeof(int));
  while (fgets(line, sizeof(line), input) != NULL){
    int new = atoi(line);
    nums[trav] = new;
    trav++;
  }

  // generate a random solution +-1
  int* soln = malloc(100 * sizeof(int));
  for (iter = 0; iter < 100; iter++){
    randsubset = rand() % SET_SIZE;
    soln[iter] = randsubset;
  }
}
