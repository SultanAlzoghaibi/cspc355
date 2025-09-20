//
// Created by Sultan Alzoghaibi on 2025-09-19.
//


#include <stdio.h>
#include <stdlib.h>  // for rand()
#include <stdbool.h>

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


int countBamboType(int bamboo, int** grid) {
    int count = 0;


    for (int i = 0; i < bamboo; i++) {
        for (int j = 0; j < bamboo; j++) {
            if (grid[i][j] == bamboo) {
                count++;
            }
        }
    }
    return count;


}

void doubleBambooSearch(int** grid, int n, FILE *log) {
    int bamboo1, bamboo2;
    printf("Enter bamboo type 1 (0–9): ");
    scanf("%d", &bamboo1);
    printf("Enter bamboo type 2 (0–9): ");
    scanf("%d", &bamboo2);

    fprintf(log, "Double search for bamboo types %d and %d\n", bamboo1, bamboo2);

    int count1 = 0, count2 = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == bamboo1) {
                fprintf(log, "(%d,%d) -> type %d\n", i, j, bamboo1);
                printf("(%d,%d) -> type %d\n", i, j, bamboo1);
                count1++;
            }
            if (grid[i][j] == bamboo2) {
                fprintf(log, "(%d,%d) -> type %d\n", i, j, bamboo2);
                printf("(%d,%d) -> type %d\n", i, j, bamboo2);
                count2++;
            }
        }
    }

    double percent1 = (double)count1 / (n * n) * 100.0;
    double percent2 = (double)count2 / (n * n) * 100.0;

    if (count1 > 0) {
        fprintf(log, "Bamboo %d percentage: %.2f%%\n", bamboo1, percent1);
        printf("bamboo1 percentage: %.2f%%\n", percent1);
    }
    else {
        fprintf(log, "Mochi will not eat any bamboo1 💀 (no %d)\n", bamboo1);

    }
    if (count2 > 0) {
        fprintf(log, "Bamboo %d percentage: %.2f%%\n", bamboo2, percent2);
        printf("bamboo2 percentage: %.2f%%\n", percent2);
    }
    else {
        fprintf(log, "Mochi will not eat any bamboo2 💀 (no %d)\n", bamboo2);
        printf("bamboo2 percentage: %.2f%%\n", percent2);
    }
    fprintf(log, "\n");
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
    FILE *log = fopen("log.txt", "w");
    for (int i = 0; i < 2; i++) {
        int bamboo;
        do {
            printf("Enter a bamboo type to search (0–9), or enter -1 to perform double search: ");
            scanf("%d", &bamboo);

            if (bamboo == -1 ) {
                break;
            }
            if (bamboo < 0 || bamboo > 9) {
                printf("Invalid bamboo\n");
            } else {
                break;
            }
        } while (true);

        if (bamboo == -1 ) {
            doubleBambooSearch(grid, n, log);
            printf("attempt 2");
            fprintf(log, "attempt 2 \n");
            doubleBambooSearch(grid, n, log);
            return 0;

        }

        if (!log) {
            perror("Failed to open log file");
            exit(1);
        }

        fprintf(log, "Forest grid (%dx%d):\n", n, n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                fprintf(log, "%d ", grid[i][j]);
            }
            fprintf(log, "\n");
        }
        fprintf(log, "\n");


        printf("vallid bamboo\n");
        fprintf(log, "Search for bamboo type %d\n", bamboo);
        int count = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == bamboo) {
                    fprintf(log, "(%d,%d)\n", i, j);
                    printf("(%d,%d)\n", i, j);
                    count++;
                }
            }

        }

        double percent = (double)count / (n * n) * 100.0;

        if (percent > 0.0) {
            fprintf(log, "Percentage: %.2f%%\n\n", percent);
            printf("percent = %f\n", percent);
        } else {
            fprintf(log, "mochi will starve 💀\n");
            printf("0 percent bambo type, mochi gonna starve 💀\n");
        }

        fprintf(log, "attempt 2 \n");
    }
    fclose(log);

    // free memory
    for (int i = 0; i < n; i++) free(grid[i]);
    free(grid);

    return 0;
}
