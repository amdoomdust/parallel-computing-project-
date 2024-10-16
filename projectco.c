#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to find prime factors of a number
void prime_factors(long long int n, int rank) {
    printf("Process %d: Prime factors of %lld: ", rank, n);
    for (long long int i = 2; i <= n; i++) {
        while (n % i == 0) {
            printf("%lld ", i);
            n /= i;
        }
    }
    printf("\n");
}

int main(int argc, char** argv) {
    int rank, size;
    long long int n = 50678; // Number to factorize
    double start_time, end_time, total_start_time, total_end_time;
    double cpu_time_used;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Record the start time for the entire program by process 0
    if (rank == 0) {
        total_start_time = MPI_Wtime();
    }

    start_time = MPI_Wtime();

    // Each process finds prime factors of a subset of numbers
    long long int start = rank * (n / size) + 1;
    long long int end = (rank + 1) * (n / size);
    if (rank == size - 1) {
        // Adjust for the last process
        end = n;
    }

    // Find prime factors for the subset of numbers
    for (long long int i = start; i <= end; i++) {
        prime_factors(i, rank);
    }

    end_time = MPI_Wtime();

    printf("Process %d: Execution time: %f seconds\n", rank, end_time - start_time);

    // Wait for all processes to synchronize
    MPI_Barrier(MPI_COMM_WORLD);

    // Record the end time for the entire program by process 0
    if (rank == 0) {
        total_end_time = MPI_Wtime();
        printf("Total execution time across all processes: %f seconds\n", total_end_time - total_start_time);
    }

    MPI_Finalize();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("CPU time used: %f seconds\n", cpu_time_used);
     printf("speedup time : %f seconds\n", (115.067/cpu_time_used));

    return 0;
}
