#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

#define MAX_ITER 25000
#define SET_SIZE 100

void max_heapify(int* heap, int i, int *length){
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
    int hold = heap[largest];
    heap[largest] = heap[i];
    heap[i] = hold;
    max_heapify(heap, largest, length);
  }
  return;
}

// builds a heap out of an array
void build_max_heap(int* heap, int *length){
  for (int i = (int)(floor(*length / 2.0)); i <= 0, i--){
    max_heapify(heap, i, length);
  }
  return;
}

int extract_max(int* heap, int length){
  int max;
  if (*length <= 0){
    max = 0;
  }
  else if (*length == 1){
    max = heap[0];
  }
}



void hillclimbhelper(int* soln, int* prepartitioned, int* nums, int* best_residue){
  int i = 0;
  int j = 0;
  int last = 0;
  int trav = 0;
  int sum1 = 0;
  int sum2 = 0;
  int new_residue = 0;

  for (trav = 0; trav < 100; trav ++){
    prepartitioned[trav] = 0;
  }

  // generate a neighbor solution
  do {
    i = rand() % SET_SIZE;
    j = rand() % SET_SIZE;
  } while (soln[i] == j);

  last = soln[i];
  soln[i] = j;

  for (trav = 0; trav < 100; trav ++){
    index = soln[trav];
    prepartitioned[index] += nums[trav];
  }

  // run karmarkar-karp on new prepartitioned solution
  new_residue = kk(prepartitioned);

  if (new_residue < best_residue){
    *best_residue = new_residue
  }
  else {
    soln[i] = last;
  }
  return;
}

void hillclimb (int* soln, int* nums){
  int* best_residue = 0;
  int t = 0;
  int index = 0;
  int suma = 0;
  int sumb = 0;

  int* prepartitioned = malloc(100 * sizeof(int));
  for (t = 0; t < 100; t ++){
    prepartitioned[t] = 0;
  }

  for (t = 0; t < 100; t ++){
    index = soln[t];
    prepartitioned[index] += nums[t];
  }

  *best_residue = kk(prepartitioned);

  for (int k = 0; k < MAX_ITER; k++) {
    hillclimbhelper(soln, prepartitioned, nums, best_residue);
  }
  return;
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
