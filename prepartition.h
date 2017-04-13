#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include "kk.c"
#define MAX_ITER 25000
#define SET_SIZE 100

// functions for prepartitioned solution representation
long pp_repeated_random(int n, long nums[n]) {
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
    long *partition = calloc(n, sizeof(long));
    for (int i = 0; i < n; i++) {
        soln[i] = rand() % n;
        partition[soln[i]] += nums[i];
    }
    long best_residue = karmarkar_karp(n, partition);

    for (int i = 0; i < MAX_ITER; i++) {
        long *neighbor = pp_rand_neighbor(n, soln);
        for (int j = 0; j < n; j++)
            partition[j] = 0;

        for (int j = 0; j < n; j++)
            partition[neighbor[j]] += nums[j];

        long res = karmarkar_karp(n, partition);
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
    long *partition = calloc(n, sizeof(long));
    for (int i = 0; i < n; i++) {
        soln[i] = rand() % n;
        partition[soln[i]] += nums[i];
    }
    long soln_residue = karmarkar_karp(n, partition);
    long best_residue = soln_residue;

    for (int i = 0; i < MAX_ITER; i++) {
        long *neighbor = pp_rand_neighbor(n, soln);
        for (int j = 0; j < n; j++)
            partition[j] = 0;

        for (int j = 0; j < n; j++)
            partition[neighbor[j]] += nums[j];

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