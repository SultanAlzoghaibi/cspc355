//
// Created by Sultan Alzoghaibi on 2025-09-30.
// A2:
/*
 * Im using an Arraylist where if theer need to more space
 * it will double in size Similar ot how is
 * Arraylist in Java (1.5x)
 * or list in python work (~1.125–1.5× depending on size.)
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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


int daysBetween(const char *date1, const char *date2) {
    struct tm d1 = {0}, d2 = {0};

    // Parse "YYYY-MM-DD"
    if (sscanf(date1, "%d-%d-%d", &d1.tm_year, &d1.tm_mon, &d1.tm_mday) != 3) {
        return 0;  // parse error
    }
    if (sscanf(date2, "%d-%d-%d", &d2.tm_year, &d2.tm_mon, &d2.tm_mday) != 3) {
        return 0;
    }

    // Adjust for struct tm format
    d1.tm_year -= 1900;
    d2.tm_year -= 1900;
    d1.tm_mon  -= 1;
    d2.tm_mon  -= 1;

    // Let mktime figure out DST
    d1.tm_isdst = -1;
    d2.tm_isdst = -1;

    time_t t1 = mktime(&d1);
    time_t t2 = mktime(&d2);

    if (t1 == (time_t)-1 || t2 == (time_t)-1) {
        // error converting
        return 0;
    }

    double secondsDiff = difftime(t2, t1);
    double days = secondsDiff / (60 * 60 * 24);

    // Round to nearest integer day
    if (days >= 0)
        return (int)(days + 0.5);
    else
        return (int)(days - 0.5);
}
// got help with chatgt withe library of #include <time.h> and implimantation


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

void addshipmentsMenu(struct shipmentArrayList *shipmentlogs, char todayDate[] ){
    do {
        char command[16];
        printf("\nEnter 'add' to input a new shipment or 'exit' to return to main menu: ");
        scanf("%15s", command);

        if (strcmp(command, "exit") == 0)
            break;
        if (strcmp(command, "add") != 0) {
            printf("❌ Invalid command. Type 'add' or 'exit'.\n");
            continue;
        }

        int type, amount, supplierId;
        char date[11];

        printf("Enter bamboo type (integer 0–9): ");
        if (scanf("%d", &type) != 1) {
            printf("❌ Invalid type input.\n");
            while (getchar() != '\n'); // flush bad input
            continue;
        }

        printf("Enter shipment amount: ");
        if (scanf("%d", &amount) != 1) {
            printf("❌ Invalid amount input.\n");
            while (getchar() != '\n');
            continue;
        }

        printf("Enter shipment date (YYYY-MM-DD): ");
        scanf("%10s", date);

        // Validate date format
        if (strlen(date) != 10 || date[4] != '-' || date[7] != '-') {
            printf("⚠️ Invalid date format: %s\n", date);
            continue;
        }
        int year, month, day;
        if (sscanf(date, "%4d-%2d-%2d", &year, &month, &day) != 3 ||
            month < 1 || month > 12 || day < 1 || day > 31) {
            printf("⚠️ Invalid date value: %s\n", date);
            continue;
            }

        printf("Enter supplier ID: ");
        if (scanf("%d", &supplierId) != 1) {
            printf("❌ Invalid supplier input.\n");
            while (getchar() != '\n');
            continue;
        }

        int daysPassed = daysBetween(date, todayDate);

        // Skip expired (older than 7 days)
        if (daysPassed > 7) {
            printf("❌ Skipping expired shipment (Type %d, Date %s)\n", type, date);
            continue;
        }

        // Warn if expiring within 2 days
        if (daysPassed >= 5) {
            printf("⚠️  Warning: Shipment (Type %d, Date %s) expires soon!\n", type, date);
        }


        struct shipment s;
        s.type = type;
        s.amount = amount;
        s.suplierId = supplierId;
        strcpy(s.date, date);

        addShipment(shipmentlogs, s);
        printf("Shipment added successfully\n");

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
    int choice;
    do {
        printf("\n------ Sort Menu ------\n");
        printf("1 = Sort by Quantity\n");
        printf("2 = Sort by Bamboo Type\n");
        printf("3 = Sort by Date\n");
        printf("-1 = Exit Sort Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                for (int i = 1; i < shipmentlogs->size; ++i) {
                    struct shipment s = shipmentlogs->shipments[i];
                    int j = i - 1;

                    /* Move elements of arr[0..i-1], that are
                       greater than key, to one position ahead
                       of their current position */
                    while (j >= 0 &&  shipmentlogs->shipments[j].amount < s.amount) {
                        shipmentlogs->shipments[j + 1] = shipmentlogs->shipments[j];
                        j -= 1;
                    }
                    shipmentlogs->shipments[j + 1] = s;
                }
                // source but replaced with variable with my own
                // https://www.geeksforgeeks.org/dsa/insertion-sort-algorithm/


                printf("✅ Sorted by Quantity (high → low)\n");
                break;
            case 2:
                for (int i = 1; i < shipmentlogs->size; ++i) {
                    struct shipment s = shipmentlogs->shipments[i];
                    int j = i - 1;

                    /* Move elements of arr[0..i-1], that are
                       greater than key, to one position ahead
                       of their current position */
                    while (j >= 0 &&  shipmentlogs->shipments[j].type > s.type) {
                        shipmentlogs->shipments[j + 1] = shipmentlogs->shipments[j];
                        j -= 1;
                    }
                    shipmentlogs->shipments[j + 1] = s;
                }

                printf("✅ Sorted by Bamboo Type\n");
                break;
            case 3:

                for (int i = 1; i < shipmentlogs->size; i++) {
                    struct shipment key = shipmentlogs->shipments[i];
                    int j = i - 1;

                    // Compare date strings lexicographically
                    while (j >= 0 && strcmp(shipmentlogs->shipments[j].date, key.date) > 0) {
                        shipmentlogs->shipments[j + 1] = shipmentlogs->shipments[j];
                        j--;
                    }
                    shipmentlogs->shipments[j + 1] = key;
                }

                printf("✅ Sorted by Date (newest first)\n");
                break;
            case -1:
                printf("🔙 Returning to main menu...\n");
                return; // exits the function
            default:
                printf("❌ Invalid choice. Please try again.\n");
        }

    } while (1);


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
        fprintf(reportFile, "%d. %d \n", i+1, typeTotalsCopy[i]);
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



void loadFile(struct shipmentArrayList *shipmentlogs, char filename[], char todayDate[]) {
    FILE *shipmentFile = fopen(filename, "r");
    if (shipmentFile == NULL) {
        printf("File not found\n");
        exit(1);
    }
    char shipmentLine[256];
    int count;
    int lineNumber = 0;

    while (fgets(shipmentLine, sizeof(shipmentLine), shipmentFile) != NULL) {
        lineNumber++;
        int type, amount, supplierId;
        char date[11];  // +1 for '\0'
        int parsed = sscanf(shipmentLine, "%d %d %10s %d",
                            &type, &amount, date, &supplierId);


        // If not all fields are read correctly → show warning and skip
        if (parsed != 4) {
            printf("WARNING ⚠️ : Invalid or incomplete data on line %d: %s \n", lineNumber, shipmentLine);
            continue;
        }


        // Optional: Validate date format (basic check)
        if (strlen(date) != 10 || date[4] != '-' || date[7] != '-') {
            printf("Warning ⚠️: Invalid date format on line %d: %s", lineNumber, date);
            continue;
        }

        int year, month, day;
        sscanf(date, "%4d-%2d-%2d", &year, &month, &day);

        // Simple bounds check
        if (month < 1 || month > 12 || day < 1 || day > 31) {
            printf("⚠️ Warning: Invalid date value on line %d: %s\n", lineNumber, date);
            continue;
        }

        int daysPassed = daysBetween(date, todayDate);


        if (daysPassed > 7) {
            printf("❌ Skipping expired shipment (Type %d, Date %s)\n", type, date);
            continue;
        }

        if (daysPassed >= 5) {
            printf("⚠️  Warning: Shipment (Type %d, Date %s) expires soon!\n", type, date);
        }



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

    char todayDate[11];
    do {
        printf("Enter today's date (YYYY-MM-DD): ");
        scanf("%10s", todayDate);
        //strcpy(todayDate, "2025-10-05");
        if (strlen(todayDate) != 10 || todayDate[4] != '-' || todayDate[7] != '-') {
            printf("Warning: Invalid date format)");
            continue;
        }
        break;
    } while (1);

    char *fileName = argv[1];
    printf("%s\n", fileName);
    loadFile(&shipmentlogs, fileName, todayDate);
    //printShipmentLogs(shipmentlogs);
    do {
        printf("------ You are at the Home Menu ------\n");
        printf("First 10 shipments in shipmentlogs \n");
        printNShipment(shipmentlogs, printNumber);
        printf("Which menu to go to: 1 = add ships, 2 = search ships, 3 = remove ships, 4 = sort ships, 5 = generate report, -1 = exit: \n");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Call function to add shipments
                addshipmentsMenu(&shipmentlogs, todayDate);
                break;
            case 2:
                searchShipmentMenu(&shipmentlogs);
                break;
            case 3:
                deleteShipmentMenu(&shipmentlogs);

                break;
            case 4:
                sortShipmentMenu(&shipmentlogs);
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

