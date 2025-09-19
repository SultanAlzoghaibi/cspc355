//
// Created by Sultan Alzoghaibi on 2025-09-19.
//


#include <stdio.h>
#include <stdlib.h>  // for rand()

int** createRandom2dGrid(int n) {



    // allocates teh row at size n
    int** grid = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        // allocates teh col at size n
        grid[i] = (int*) malloc(n * sizeof(int));

        for (int j = 0; j < n; j++) {
            grid[i][j] = rand() % (9 + 1);
        }
    }

    return grid;

}
void printGrid(int** grid, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");

    }
}

int main(int argc, const char * argv[]) {
    if (argc != 2) {
        printf("Usage: %s <size>\n", argv[0]);
        return 1;
    }
    // atoi = ASCII to integer
    int n = atoi(argv[1]);
    printf("n = %d\n", n);

    int** grid = createRandom2dGrid(n);
    printGrid(grid, n);

    // free memory
    for (int i = 0; i < n; i++) free(grid[i]);
    free(grid);

    return 0;
}
