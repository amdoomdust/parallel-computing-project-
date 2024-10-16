#include <stdio.h>
#include <math.h>
#include <time.h>

// Function to perform prime factorization for a given number
void primeFactorization(long long n) {
    // Print the prime factors
    if (n == 1) {
        printf("1 is not a prime number.\n");
        return;
    }
    if (n == 2) {
        printf("%lld\n", n);
        return;
    }

    while (n % 2 == 0) {
        printf("%d ", 2);
        n = n / 2;
    }

    for (int i = 3; i <= (int)sqrt(n); i = i + 2) {
        while (n % i == 0) {
            printf("%d ", i);
            n = n / i;
        }
    }

    if (n > 2)
        printf("%lld ", n);
}

int main() {
    long long N;
    clock_t start_time, end_time;
    double execution_time;

    // Ask for input for N
    printf("Enter the value of N: ");
    scanf("%lld", &N);

    // Start measuring execution time
    start_time = clock();

    // Iterate from 2 to N and find prime factors
    for (long long i = 2; i <= N; ++i) {
        printf("Prime factors of %lld are: ", i);
        primeFactorization(i);
        printf("\n");
    }

    // End measuring execution time
    end_time = clock();
    execution_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    // Print execution time
    printf("Total execution time: %f seconds\n", execution_time);

    return 0;
}
