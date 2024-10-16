#include <stdio.h>
#include <omp.h>
#include <math.h>

// Function to perform prime factorization for a given number
void primeFactorization(long long n) {
    // Get the thread ID
    int thread_id = omp_get_thread_num();

    // Print thread ID and prime factors
    while (n % 2 == 0) {
        printf("Thread %d: %d\n", thread_id, 2);
        n = n / 2;
    }

    for (int i = 3; i <= (int)sqrt(n); i = i + 2) {
        while (n % i == 0) {
            printf("Thread %d: %d\n", thread_id, i);
            n = n / i;
        }
    }

    if (n > 2)
        printf("Thread %d: %lld\n", thread_id, n);
}

int main() {
    long long N;
    int num_threads;
    double start_time, end_time;

    // Ask for input for N and number of threads
    printf("Enter the value of N: ");
    scanf("%lld", &N);
    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);

    // Start measuring execution time
    start_time = omp_get_wtime();

    // Set the number of threads
    omp_set_num_threads(num_threads);

    // Perform prime factorization
    printf("Prime factors of numbers from 2 to %lld are: \n", N);
    #pragma omp parallel for
    for (long long i = 2; i <= N; ++i) {
        primeFactorization(i);
    }

    // End measuring execution time
    end_time = omp_get_wtime();

    // Calculate and print execution time
    double execution_time = end_time - start_time;
    printf("Execution time: %f seconds\n", execution_time);
    printf("Speedup time: %f \n", 115.067000 / execution_time);


    return 0;
}
