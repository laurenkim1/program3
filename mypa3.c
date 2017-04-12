#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define MAX_ITER 25000
#define SET_SIZE 100

int repeatedrandomhelper (int* soln, int* temp_soln, int* nums, int best_residue){
  int i = 0;
  int j = 0;
  int move_or_swap = 0;
  int trav = 0;
  int sum1 = 0;
  int sum2 = 0;
  int new_residue = 0;

  for (int k = 0; k < MAX_ITER; k++) {
    do {
      i = rand() % SET_SIZE;
      j = rand() % SET_SIZE;
    } while (randindexi == randindexj);

    soln[i] = -1 * soln[i];

    move_or_swap = rand() % 2;
    if (move_or_swap == 0){
      soln[j] = -1 * soln[j];
    }
    else {
      soln[j] = soln[j];
    }

    for (trav = 0; trav < 100; trav ++){
      if (soln[trav] = 1) {
        sum1 += nums[trav];
      }
      else {
        sum2 += nums[trav];
      }
    }

    new_residue = abs(sum1 - sum2);
    if (new_residue < best_residue){
      best_residue = new_residue;
    }
    sum1 = 0;
    sum2 = 0;
  }

  return best_residue;
}

int repeatrandom (int* soln, int* nums){
  int best_residue = 0;
  for (int b = 0; b < 100; b++){
    best_residue += nums[b];
  }

  return best_residue;
}


int main (void) {
  // seeding random number generator once
  time_t seconds;
  time(&seconds);
  srand((unsigned int) seconds);

  int iter;
  int randsubset;

  // generate a random solution +-1
  int* soln = malloc(100 * sizeof(int))
  for (iter = 0; iter < 100; iter++){
    randsubset = rand() % 2;
    if (randsubset == 0) {
      soln[iter] = -1;
    }
    else {
      soln[iter] = 1;
    }
  }

  int* nums = malloc(100 * sizeof(int))

  repeatrandom(soln, nums);
}
