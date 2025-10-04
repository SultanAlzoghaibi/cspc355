//
// Created by Sultan Alzoghaibi on 2025-09-30.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int initialCapacityOfArrayList = 32;
int printNumber = 10;
struct shipment {
    int type;
    int amount;
    char date[11];
    int suplierId;
};

struct shipmentArrayList {
    struct shipment *shipments;
    int size;
    int capacity;
};
void printShipmentLogs(struct shipmentArrayList shipmentlogs) {
    for (int i = 0; i < shipmentlogs.size; i++) {
        struct shipment s = shipmentlogs.shipments[i];
        printf("Type: %d | Amount: %d | Date: %s | Supplier: %d\n",
               s.type, s.amount, s.date, s.suplierId);
    }

}

void initShipmentArrayList(struct shipmentArrayList *list, int initialCapacity) {
    list->shipments = malloc(initialCapacity * sizeof(struct shipment));
    list->size = 0;
    list->capacity = initialCapacity;
}

void printNShipment(struct shipmentArrayList shipmentlogs, int n) {
    for (int i = 0; i < n; i++) {
        if (i >= shipmentlogs.size) {
            printf("null\n");
        } else {
            struct shipment s = shipmentlogs.shipments[i];
            printf("Type: %d | Amount: %d | Date: %s | Supplier: %d\n",
                   s.type, s.amount, s.date, s.suplierId);
        }

    }

}


void addShipment(struct shipmentArrayList *shipmentlogs, struct shipment shipment) {
    int addIdx = (shipmentlogs->size);

    if (addIdx >= shipmentlogs->capacity) {
        shipmentlogs->capacity *= 2;
        shipmentlogs->shipments = realloc(
            shipmentlogs->shipments,
        shipmentlogs->capacity * sizeof(struct shipment)
        );

        if (shipmentlogs->shipments == NULL) {
            perror("Failed to malloc, not initialized");
            exit(1);
        }

    }

    shipmentlogs->shipments[addIdx] = shipment;
    shipmentlogs->size++;

}

void addshipmentsMenu(struct shipmentArrayList *shipmentlogs){
    do {
        char response[512];
        printf("Enter shipment (<type> <amount> <date> <supplier>) OR 'exit' to break: \n");
        scanf("%s", &response);
        response[strcspn(response, "\n")] = '\0';

        if (strcmp(response, "exit") == 0) {
            break;
        } else {
            if (fgets(response, sizeof(response), stdin) == NULL) break;
            int type, amount, supplierId;
            char date[11];
            int fileReadnum = sscanf(response, "%d %d %10s %d", &type, &amount, date, &supplierId);

            if (fileReadnum != 4) {
                printf("Invalid input\n");
                int type, amount, supplierId;
                continue;
            }
            struct shipment s;
            s.type = type;
            s.amount = amount;
            s.suplierId = supplierId;
            strcpy(s.date, date);

            addShipment(&shipmentlogs, s);
            printf("Shipment added successfully\n");
        }
    } while (1);
}


void deleteShipment(struct shipmentArrayList *shipmentlogs, int rangeS, int rangeE) {
    int sizeRemoved = rangeE - rangeS + 1;

    //printf("BEFORE\n");
    //printShipmentLogs(*shipmentlogs);
    // im shifting the array after teh cut off to the beinning of the cut off
    memmove(&shipmentlogs->shipments[rangeS],
         &shipmentlogs->shipments[rangeE + 1],
         (shipmentlogs->size - rangeE - 1) * sizeof(struct shipment));

    shipmentlogs->size -= sizeRemoved;
    int newSize = shipmentlogs->size;
    //deleting extra memory
    // Chatgtp said to use this bc,
    // you’re filling the raw bytes that make up those struct shipment objects with zeroes.
    // aka a ay of making them emply stucts that cna tbe used
    memset(&shipmentlogs->shipments[newSize], 0,
           (shipmentlogs->capacity - newSize) * sizeof(struct shipment));


    //printf("AFTER\n");
    //printShipmentLogs(*shipmentlogs);
    printf("%d\n", newSize);


//todo: You do a better more effcient way to split with some math in cses of mutple cap/2 being needed
    if ( (shipmentlogs->size < (shipmentlogs->capacity) / 2 ) &&
        shipmentlogs->capacity > initialCapacityOfArrayList) {

        shipmentlogs->capacity = shipmentlogs->capacity / 2;

        //Were deallocating the memory of the arraylist by half bc its no longer needed
        shipmentlogs->shipments = realloc(

            shipmentlogs->shipments,
             shipmentlogs->capacity * sizeof(struct shipment)
);

    }
}
void deleteShipmentMenu(struct shipmentArrayList *shipmentlogs) {
    do {
        char response[512];
        printNShipment(*shipmentlogs, printNumber);
        printf("---------- DELETING MENU --------------");
        printf("Enter shipment index range to delete (e.g., 2-5 both inclusive), max index = %d\n", shipmentlogs->size - 1);
        printf("Or type 'exit' to return to the main menu:\n");
        scanf("%s", &response);
        response[strcspn(response, "\n")] = '\0';

        if (strcmp(response, "exit") == 0) {
            break;
        } else {
            int startIdx, endIdx;
            int parsed = sscanf(response, "%d-%d", &startIdx, &endIdx);
            if (parsed != 2) {
                printf("Invalid input. Please enter two numbers or 'exit'.\n");
                continue;
            }
            printf("You entered: start = %d, end = %d\n", startIdx, endIdx);
            //todo: catch those inputs aps the max
            deleteShipment(shipmentlogs, startIdx, endIdx);
            // You can now call deleteShipmentRange(shipmentlogs, startIdx, endIdx);
            // But for now, just UI
        }
    } while (1);
}
void searchShipmentMenu(struct shipmentArrayList *shipmentlogs) {
    char response[128];
    int choice;

    do {
        printf("------ Search Menu ------\n");
        printf("1 = Search by bamboo type\n");
        printf("2 = Search by supplier ID\n");
        printf("3 = Search by date range\n");
        printf("-1 = Return to main menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == -1) {
            break;
        }

        if (choice == 1) {  // Bamboo type
            int type;
            printf("Enter bamboo type (0–9): ");
            scanf("%d", &type);
            for (int i = 0; i < shipmentlogs->size; i++) {
                if (shipmentlogs->shipments[i].type == type) {
                    struct shipment s = shipmentlogs->shipments[i];
                    printf("Type: %d | Amount: %d | Date: %s | Supplier: %d\n",
                           s.type, s.amount, s.date, s.suplierId);
                }
            }

        } else if (choice == 2) {  // Supplier ID
            int supplierId;
            printf("Enter supplier ID: ");
            scanf("%d", &supplierId);
            for (int i = 0; i < shipmentlogs->size; i++) {
                if (shipmentlogs->shipments[i].suplierId == supplierId) {
                    struct shipment s = shipmentlogs->shipments[i];
                    printf("Type: %d | Amount: %d | Date: %s | Supplier: %d\n",
                           s.type, s.amount, s.date, s.suplierId);
                }
            }

        } else if (choice == 3) {  // Date range
            char startDate[11], endDate[11];
            printf("Enter start date (YYYY-MM-DD): ");
            scanf("%s", startDate);
            printf("Enter end date (YYYY-MM-DD): ");
            scanf("%s", endDate);

            for (int i = 0; i < shipmentlogs->size; i++) {
                if (strcmp(shipmentlogs->shipments[i].date, startDate) >= 0 &&
                    strcmp(shipmentlogs->shipments[i].date, endDate) <= 0) {
                    struct shipment s = shipmentlogs->shipments[i];
                    printf("Type: %d | Amount: %d | Date: %s | Supplier: %d\n",
                           s.type, s.amount, s.date, s.suplierId);
                }
            }

        } else {
            printf("Invalid choice, try again.\n");
        }
        // use chatgtp after knwoing hwo to the frist one, bc repetition
    } while (1);
}

int compareDesc(const void *a, const void *b) {
    int A = *(int *)a;
    int B = *(int *)b;
    return B - A;
}

void sortShipmentMenu(struct shipmentArrayList *shipmentlogs) {


}

void generateReport(struct shipmentArrayList *shipmentlogs) {
    FILE *reportFile = fopen("A2/report.txt", "w");
    if (reportFile == NULL) {
        printf("Failed to open report file.\n");
        return;
    }
    int typeTotals[10] = {0};
    int supplierTotals[1000] = {0}; // suplyer less then 1000
    int totalQuantity = 0;

    for (int i = 0; i < shipmentlogs->size; i++) {
        struct shipment s = shipmentlogs->shipments[i];
        typeTotals[s.type] += 1;
        supplierTotals[s.suplierId] += s.amount;
        totalQuantity += s.amount;
    }
    fprintf(reportFile, "Total bamboo stock:\n");
    for (int i = 0; i < 10; i++) {
        if (typeTotals[i] > 0) {
            fprintf(reportFile, "Type %d: %d\n", i, typeTotals[i]);
        }
    }

    fprintf(reportFile, "\n");
    int typeTotalsCopy[10] = {0};
    memcpy(typeTotalsCopy, typeTotals, sizeof(typeTotals));
    qsort(typeTotalsCopy, 10, sizeof(int), compareDesc);
    fprintf(reportFile, "Top 3 bambo types:\n");
    for (int i = 0; i < 3; i++) {
        fprintf(reportFile, "%d. %d ", i+1, typeTotalsCopy[i]);
    }
    fprintf(reportFile, "\n");
    fprintf(reportFile, "\nSupplier statistics:\n");
    for (int i = 0; i < 1000; i++) {
        if (supplierTotals[i] > 0) {
            float percent = ((float)supplierTotals[i] / totalQuantity) * 100.0f;
            fprintf(reportFile, "Supplier %d: %.1f%%\n", i, percent);
        }
    }

    fclose(reportFile);
    printf("✅ Report generated successfully: report.txt\n");

}



void loadFile(struct shipmentArrayList *shipmentlogs, char filename[]) {
    FILE *shipmentFile = fopen(filename, "r");
    if (shipmentFile == NULL) {
        printf("File not found\n");
        exit(1);
    }
    char shipmentLine[256];
    int count;

    while (fgets(shipmentLine, sizeof(shipmentLine), shipmentFile) != NULL) {

        int type, amount, supplierId;
        char date[11];  // +1 for '\0'
        sscanf(shipmentLine, "%d %d %10s %d",
        &type, &amount, date, &supplierId);

        struct shipment s;
        s.type = type;
        s.amount = amount;
        s.suplierId = supplierId;
        strcpy(s.date, date);

        addShipment(shipmentlogs, s);

    }

    fclose(shipmentFile);

}


// -----------------MAIN---------MAIN------MAIN-----MAIN-------MAIN----------------------------------------------
int main(int argc, char * argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    struct shipmentArrayList shipmentlogs;
    initShipmentArrayList(&shipmentlogs, initialCapacityOfArrayList);

    char *fileName = argv[1];
    printf("%s\n", fileName);
    loadFile(&shipmentlogs, fileName);
    //printShipmentLogs(shipmentlogs);
    do {
        printf("------ You are at the Home Menu ------\n");
        printf("First 5 shipments in shipmentlogs \n");
        printNShipment(shipmentlogs, printNumber);
        printf("Which menu to go to: 1 = add ships, 2 = search ships, 3 = remove ships, 4 = sort ships, 4 = generate report, -1 = exit: \n");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Call function to add shipments
                addshipmentsMenu(&shipmentlogs);
                break;
            case 2:
                // TODO: Call search shipments function
                searchShipmentMenu(&shipmentlogs);
                break;
            case 3:
                // TODO: Call remove shipments function
                deleteShipmentMenu(&shipmentlogs);

                break;
            case 4:
                // TODO: Call sort shipments function
                // sortShipments(&shipmentlogs);
                break;
            case 5:
                generateReport(&shipmentlogs);
                break;
            case -1:
                // Exit menu loop
                printShipmentLogs(shipmentlogs);

                return 0;
            default:
                printf("Invalid option, try again.\n");
        }
        // Chatgtp made this do-while loop to speed up work flow.

    } while (1);

    return 0;
}

