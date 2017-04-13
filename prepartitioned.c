#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include <string.h>

#define MAX_ITER 25000
#define SET_SIZE 100


long pp_repeated_random(int n, long* nums){
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

    long best_residue = kk(n, prepartitioned);

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
        long res = kk(n, prepartitioned);
        if (res < best_residue)
            best_residue = res;
    }
    free(soln);
    free(prepartitioned);
    return best_residue;
}

long* pp_rand_neighbor(int n, long soln[n]) {
    long *neighbor = malloc(n * sizeof(long));
    memcpy(neighbor, soln, n * sizeof(long));

    do {
      i = rand() % SET_SIZE;
      j = rand() % SET_SIZE;
    } while (soln[i] == j);

    neighbor[i] = j;

    return neighbor;
}

long pp_hillclimb(int n, long nums[n]) {
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

    long best_residue = kk(n, prepartitioned);

    for (int k = 0; k < MAX_ITER; k++) {
        long *neighbor = pp_rand_neighbor(n, soln);
        for (t = 0; t < 100; t ++){
            prepartitioned[t] = 0;
        }

        for (t = 0; t < 100; t ++){
            index = neighbor[t];
            prepartitioned[index] += nums[t];
        }
        long res = kk(n, prepartitioned);
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

long pp_annealing(int n, long nums[n]) {
  ...
}
