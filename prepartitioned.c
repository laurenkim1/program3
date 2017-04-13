#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include <string.h>


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
