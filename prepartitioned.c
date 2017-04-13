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
            soln[j] = rand() % SET_SIZE;
            partition[j] = 0;
        }
        for (i = 0; i < n; i ++)
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
    int i = 0;
    int j = 0;

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
    long index = 0;
    int randsubset = 0;

    long *soln = malloc(n * sizeof(long));
    for (iter = 0; iter < 100; iter++){
        randsubset = rand() % SET_SIZE;
        soln[iter] = randsubset;
    }

    long* prepartitioned = malloc(n * sizeof(long));
    for (t = 0; t < 100; t ++){
        prepartitioned[t] = 0;
    }

    for (t = 0; t < 100; t ++){
        index = soln[t];
        prepartitioned[index] += nums[t];
    }

    long best_residue = karmarkar_karp(n, prepartitioned);

    for (int k = 0; k < MAX_ITER; k++) {
        long *neighbor = pp_rand_neighbor(n, soln);
        for (t = 0; t < 100; t ++){
            prepartitioned[t] = 0;
        }

        for (t = 0; t < 100; t ++){
            index = neighbor[t];
            prepartitioned[index] += nums[t];
        }
        long res = karmarkar_karp(n, prepartitioned);
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
    int iter = 0;
    int t = 0;
    long index = 0;
    int randsubset = 0;

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

    long soln_residue = karmarkar_karp(n, prepartitioned);
    long best_residue = soln_residue;

    for (int k = 0; k < MAX_ITER; k++) {
        long *neighbor = pp_rand_neighbor(n, soln);
        for (t = 0; t < 100; t ++){
            prepartitioned[t] = 0;
        }

        for (t = 0; t < 100; t ++){
            index = neighbor[t];
            prepartitioned[index] += nums[t];
        }
        long res = karmarkar_karp(n, prepartitioned);

        if (res < soln_residue) {
            free(soln);
            soln_residue = res;
            soln = neighbor;
        } else {
            double prob = exp(-(res - soln_residue) / T(k));
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

    float start;
    float end;

    start = clock();
    printf("Karmarkar-Karp:     %8lu | ", karmarkar_karp(SET_SIZE, nums));
    end = clock();
    printf("%.3f ms\n", 1000 * (double) (end - start)/CLOCKS_PER_SEC);

    for (int trials = 0; trials < 100; trials++){
        for (int new = 0; new < SET_SIZE; new++){
            nums[new] = rand64();
        }
        karmarkar_karp(SET_SIZE, nums);

        // standard solution representation trials
        printf("Standard: \n");
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
}
