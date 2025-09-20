# Search Algorithm Used in This Assignment

## Overview

The search algorithm implemented in this assignment is designed to find a specific type of bamboo within a grid. The process involves initializing a grid with various bamboo types, performing a search for the desired bamboo type, and logging the results including the percentage of the target bamboo found.

## Algorithm Description

1. **Grid Initialization**
   - The grid is represented as a two-dimensional array.
   - Each cell in the grid contains a bamboo type, randomly assigned or predefined.
   - Bamboo types could be represented as strings or integers, depending on the implementation.

2. **Searching**
   - The algorithm iterates over each cell in the grid.
   - For each cell, it checks if the bamboo type matches the target bamboo type being searched.
   - It keeps a count of how many times the target bamboo is found.
   - The search algorithm has a time complexity of O(n), where n is the dimension of the grid to the power of 2.

3. **Logging**
   - After the search completes, the algorithm calculates the percentage of the grid occupied by the target bamboo type.
   - The results are logged or printed, showing the count and percentage of the target bamboo found.

## Example

Consider the following 3x3 grid with bamboo types represented by numbers:

|   |   |   |
|---|---|---|
| 1 | 2 | 1 |
| 3 | 1 | 2 |
| 2 | 3 | 1 |

### Searching for Bamboo Type: `1`

- The algorithm scans each cell:
  - Finds `1` in positions (0,0), (0,2), (1,1), and (2,2).
- Total cells: 9
- Target bamboo `1` count: 4

### Output

```
Bamboo type '1' found 4 times.
Percentage of '1' in the grid: 44.44%
```

This output indicates that nearly half of the grid cells contain the bamboo type `1`.
