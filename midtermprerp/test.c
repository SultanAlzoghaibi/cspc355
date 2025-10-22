
#include <stdio.h>;

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


int secondLargest() {
    int n = 5;
    int arr[5] = { 1, 2, 3, 4, 5};

    int largest = -21771777;
    int secondLargest = -21771777;
    if (n <= 1) {
        printf("there is no second largest");
        return 0;
    }
    for (int i = 0; i < n; i++) {

        if (arr[i] >= largest) {
            int temp = largest;
            largest = arr[i];
            secondLargest = temp;
        }
        else if ( arr[i] > secondLargest) {
            secondLargest = arr[i];
        }

    }
    printf("Second largest element is %d\n", secondLargest);
    return 0;


}
int allElements() {
    int arrSize;
    printf("enter a num for arrSize");
    scanf("%d", &arrSize);
    int n;
    int arr[n];

    for (int i = 0; i < arrSize; i++) {
        printf("enter a num at index %d", i);

        scanf("%d", &n);
        arr[i] = n;
    }

}
int allElements2() {

    int arr[] = {1,2,3,5};
    int *ptr = arr;
    int total = 0;
    for (int i = 0; i < 4; i++) {
        total += *(ptr + i);
    }
    printf("Sum: %d", total);

    return 0;
}


in
int main() {
    allElements2();




}