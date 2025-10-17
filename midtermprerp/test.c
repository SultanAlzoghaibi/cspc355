
#include <stdio.h>;


int fib() {
// 0, 1, 1, 2, 3, 5, 8, 13...
    int fib0 = 0;
    int fib1 = 1;
    int n;
    printf("enter a n for fib: \n");
    scanf("%d",&n );

    if ( n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    int sum;
    for (int i = 1; i < n; i++) {
        int sum = fib0 + fib1;
        fib0 = fib1;
        fib1 = sum;

    }
    printf("fib of %d is %d.",n,  fib1);
    return 0;
}


int isPrime() {
    printf("enter a number (postive)");
    int isPrime = 1;

    int n;
    scanf("%d", &n);

    if (n <= 1) {
        isPrime = 0;
    } else {
        for (int i = 2; i*i <= n; i++) {
            if (n % i == 0) {
                isPrime = 0;
                break;
            }
        }
    }
    if (isPrime) {
        printf("number %d is a prime number", n);

    } else {
        printf("number %d is not a prime number", n);
    }
    return 0;
}

int main() {
    fib();



}