# 📦 CPSC 355 – Assignment 2: Shipment Management System
**Author:** Sultan Alzoghaibi  
**Date:** 2025-09-30

---

## 🧠 Overview
This program manages shipment data using a **dynamic ArrayList** implemented in C — similar to how Java’s `ArrayList` or Python’s `list` automatically expand when they run out of space.  
It reads shipment records from a file, allows the user to **add, search, delete, sort, and generate reports**, and automatically removes **expired bamboo shipments** (older than 7 days).

---

## ⚙️ How It Works

### 1. **Data Structures**
#### `struct shipment`
Represents a single shipment:
```c
struct shipment {
    int type;          // Bamboo type ID
    int amount;        // Quantity of bamboo
    char date[11];     // Date (YYYY-MM-DD)
    int suplierId;     // Supplier ID
};
```

#### `struct shipmentArrayList`
Implements a resizable array:
```c
struct shipmentArrayList {
    struct shipment *shipments;
    int size;          // Number of current shipments
    int capacity;      // Allocated array size
};
```

The array doubles in capacity when full and shrinks when half-empty, mimicking Java/Python dynamic resizing.

---

#### 2. **Core Functionalities**

#### 🖨 `printShipmentLogs()`
Prints every shipment (type, amount, date, supplier) to stdout.

#### 🧾 `printNShipment()`
Prints the first *N* shipments; prints `null` for indices ≥ current size.

#### 🏗 `initShipmentArrayList()`
Allocates the backing array and initializes `size=0`, `capacity=initialCapacity` (default 32).

#### ➕ `addShipment()`
Appends a shipment to the end; if full, doubles capacity with `realloc()`.

#### ➕ `addshipmentsMenu()`
Interactive add-loop: parses a line `"type amount YYYY-MM-DD supplier"`, validates date, **skips expired** (>7 days old), and **warns** if expiring soon (within 2 days), then adds.

#### 🧹 `deleteShipment()`
Deletes an inclusive index range using `memmove()` to shift left; zero-fills freed tail with `memset()`; halves capacity if underused (but never below the initial capacity).

#### 🗑 `deleteShipmentMenu()`
UI wrapper for deletion: reads a `"start-end"` range, validates, and calls `deleteShipment()`.

#### 🔍 `searchShipmentMenu()`
Interactive searches by:
- **Bamboo type** (0–9)
- **Supplier ID**
- **Date range** (`start ≤ date ≤ end`, lexicographic on `YYYY-MM-DD`)

#### 🗓 `daysBetween()`
Returns whole-day difference between two `YYYY-MM-DD` dates using `mktime()`/`difftime()` (supports expiry logic).

#### 🗃 `sortShipmentMenu()`
Sorts in-place via **insertion sort**:
- **Quantity**: high → low
- **Bamboo type**: ascending
- **Date**: chronological (oldest → newest)

#### 🧮 `compareDesc()`
`qsort()` comparator for **descending** `int` values (used to rank top-3 bamboo types in the report).

#### 📊 `generateReport()`
Writes `A2/report.txt` with:
- Total count per bamboo **type**
- **Top 3** most common types (by count)
- **Supplier** contribution as a percentage of total quantity

#### ⚠️ `loadFile()`
Reads shipments from a text file, validates fields and date format, **skips expired**, warns near-expiry, then appends to the list.

#### 🚀 `main()`
Parses the input filename, captures today’s date, calls `loadFile()`, and runs the main menu loop (add/search/delete/sort/report) until exit.
---

### 3. **Program Flow**

```
main() → loadFile() → menu loop
     ↓
  [1] Add Shipment
  [2] Search Shipments
  [3] Delete Shipments
  [4] Sort Shipments
  [5] Generate Report
  [-1] Exit
```

At startup, the user enters today’s date (used to skip expired shipments).  
The menu then loops until `-1` is selected to exit.

---

## 📁 Example File Input
```
7 120 2025-09-28 101
2 140 2025-09-30 130
9 140 2025-09-30 130
5 200 2025-10-01 115
9 75  2025-10-02 120
4 50  2025-10-03 118
9 180 2025-10-05 101
```

---

## 📄 Example Report Output (`report.txt`)
```
Total bamboo stock:
Type 2: 1
Type 4: 1
Type 5: 1
Type 7: 1
Type 9: 3

Top 3 bamboo types:
1. 3 
2. 1 
3. 1 

Supplier statistics:
Supplier 101: 33.1%
Supplier 115: 22.1%
Supplier 118: 5.5%
Supplier 120: 8.3%
Supplier 130: 30.9%
```

---

## 🧰 Technical Notes
- Language: **C**
- Uses standard libraries only:  
  `<stdio.h>`, `<stdlib.h>`, `<string.h>`, `<time.h>`
- Dynamic memory handled with `malloc()`, `realloc()`, and `memset()`
- Expiry detection and date math use `mktime()` and `difftime()`
- Sorting implemented via insertion sort for clarity.