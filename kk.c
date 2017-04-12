#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include <string.h>

#define MAX_ITER 25000
#define SET_SIZE 100

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
    return (double) n;
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