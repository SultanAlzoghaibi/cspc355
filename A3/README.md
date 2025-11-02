# CPSC 355 – Assignment 3
**Student:** Sultan Alzoghaibi  
**UCID:** 30178597

---

## 📁 Files
- `assign3a.s` – Assembly program **without macros** (loop condition at top).
- `assign3a.script` – Terminal execution log for `assign3a.s`.
- `assign3b.arm` – Assembly program **with m4 macros** (loop test moved to bottom).
- `assign3b.script` – Terminal execution log for `assign3b.arm`.

---

## 🧠 Program Description
This program asks the user to enter an integer `N`, generates `N` random integers, prints each value, calculates the total sum, and determines if the sequence is:

- **Ascending**
- **Descending**
- **Unsorted**

Both versions share the same algorithm but differ in structure:
- **Version A (`assign3a.s`)** — uses raw registers and no macros.
- **Version B (`assign3b.arm`)** — uses **m4 macros** for register naming and moves the loop test to the bottom for cleaner logic flow.

---

## 🎲 Random Number Generation
The program uses the standard C library functions:
```asm
bl time       // Get current time as seed
bl srand      // Seed the random number generator
bl rand       // Generate next pseudo-random number
```

### Limiting Random Values
Random number values are limited using **0–255** to prevent integer overflow in the total sum:
```asm
and w22, w22, #0xFF
```
This ensures that all random values remain within one byte, keeping calculations safe and consistent.

### Why Limit to 0–255?
If `rand()` returns large values and we sum many of them, the 32-bit registers can overflow. By masking to 8 bits, we ensure each number fits safely within a single byte and keeps the final total realistic.

---

## 🧩 Sorting Logic
To determine if the array is **ascending**, **descending**, or **unsorted**, the program compares each newly generated number (`CURR`) to the previous one (`PREV`).

Two flags are maintained:
- `w23` → **isAscending**
- `w24` → **isDescending**

### Logic Flow:
| Comparison | Action |
|-------------|---------|
| `CURR > PREV` | Set `isAscending = 1` |
| `CURR < PREV` | Set `isDescending = 1` |
| `CURR == PREV` | No change |

At the end:
- If both `isAscending` and `isDescending` are `0` → all numbers equal → *Not sorted (flat)*
- If `isAscending = 1` and `isDescending = 0` → *Ascending order*
- If `isAscending = 0` and `isDescending = 1` → *Descending order*
- If both `isAscending = 1` and `isDescending = 1` → *Not sorted (mixed)*

This logic ensures that the array’s order is correctly classified no matter the input.

---

## 🧱 Register Usage Summary

| Register | Macro (v3b) | Purpose |
|-----------|-------------|---------|
| `w19` | `CNT` | Loop counter |
| `w20` | `LIMIT` | Number of random values (`N`) |
| `x21` | `TOTAL` | Total sum of generated values |
| `w22` | `CURR` | Current random number |
| `w23` | `ASC` | Ascending flag |
| `w24` | `DESC` | Descending flag |
| `w25` | `PREV` | Previous random number |

---

## ⚙️ How to Assemble and Run

### 🔹 Version A – Without Macros (`assign3a.s`)
```bash
as -o assign3a.o assign3a.s
gcc -o assign3a assign3a.o
./assign3a
```

Example:
```
Enter N: 3
Random: 45
Random: 120
Random: 230
Total sum: 395
Array is sorted in ascending order.
```

---

### 🔹 Version B – With Macros (`assign3b.arm`)

#### 1️⃣ Preprocess macros:
```bash
m4 assign3b.arm > assign3b.s
```

#### 2️⃣ Assemble and link:
```bash
as -o assign3b.o assign3b.s
gcc -o assign3b assign3b.o
```

#### 3️⃣ Run:
```bash
./assign3b
```

Example:
```
Enter N: 2
Random: 184
Random: 29
Total sum: 213
Array is sorted in descending order.
```

---

## 🧪 Edge Cases
If the user enters `0` or a negative number, the program prints:
```
Invalid input: N must be positive.
```
and exits cleanly without generating numbers.

---

## 🧩 Design Features in Version B
- **Macros for readability:**
  ```asm
  define(`CNT', `w19')
  define(`TOTAL', `x21')
  define(`ASC', `w23')
  define(`DESC', `w24')
  define(`PREV', `w25')
  define(`CURR', `w22')
  define(`LIMIT', `w20')
  ```
- **Loop moved to bottom** for improved readability and structure:
  ```asm
  add CNT, CNT, #1
  cmp CNT, LIMIT
  b.lt loop
  ```
  This preserves a **pre-test loop** while making flow control more intuitive.

---

## 📜 Example Script Commands

**assign3a.script**
```bash
as -o assign3a.o assign3a.s
gcc -o assign3a assign3a.o
./assign3a
```

**assign3b.script**
```bash
m4 assign3b.arm > assign3b.s
as -o assign3b.o assign3b.s
gcc -o assign3b assign3b.o
./assign3b
```

Both script files capture compilation and execution outputs for grading.

---

## ✅ Submission Notes
- Fully commented and formatted code.
- Uses `.align 4` for proper memory alignment.
- `adrp/add` pairs correctly reference static data.
- Clear use of symbolic macros in version B for maintainability.
- Both `.script` files demonstrate successful runs and correct output.
- Edge cases (zero or negative inputs) are handled safely.
- Random values are masked to 8 bits to prevent overflow and keep outputs readable.