#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define MAX_ITER 25000
#define SET_SIZE 100

void hillclimbhelper(int* soln, int* temp_soln, int* prepartitioned, int* nums, int* best_residue){
  int i = 0;
  int j = 0;
  int move_or_swap = 0;
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
  } while (randindexi == randindexj);

  temp_soln[i] = -1 * soln[i];

  move_or_swap = rand() % 2;
  if (move_or_swap == 0){
    temp_soln[j] = -1 * soln[j];
  }
  else {
    temp_soln[j] = soln[j];
  }

  for (trav = 0; trav < 100; trav ++){
    if (temp_soln[trav] == 1) {
      sum1 += nums[trav];
    }
    else if (temp_soln[trav] == -1){
      sum2 += nums[trav];
    }
  }

  new_residue = abs(sum1 - sum2);

  if (new_residue < best_residue){
    *best_residue = new_residue
    for (trav = 0; trav < 100; trav++){
      soln[trav] = temp_soln[trav];
    }
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

  *best_residue = abs(suma - sumb);

  int* temp_soln = malloc(100 * sizeof(int));

  for (int k = 0; k < MAX_ITER; k++) {
    hillclimbhelper(soln, temp_soln, prepartitioned, nums, best_residue);
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
