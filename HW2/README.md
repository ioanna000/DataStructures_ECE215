
# Sorting Algorithms Implementation in C

A comprehensive implementation of various sorting algorithms using doubly linked lists in C. This project demonstrates both comparison-based and non-comparison-based sorting techniques with performance metrics.

## Overview

This project implements 8 different sorting algorithms that operate on a doubly linked list data structure containing student records (AEM number and name). The implementation includes:

- **Comparison-based sorts**: Insertion, Selection, Bubble, Quick, Heap, and Merge Sort
- **Non-comparison-based sorts**: Radix Sort (LSD and MSD variants)

Each algorithm tracks performance metrics including comparisons, copies/swaps, and execution time.

## Project Structure

\`\`\`
├── dlist.h/c          # Doubly linked list implementation
├── sort.h/c           # Sorting algorithms implementation
├── type_t.h/c         # Student data type definition and operations
├── test.c             # Main test driver program
├── Makefile           # Build and test automation
└── students-*.txt     # Test data files
\`\`\`

## Sorting Algorithms

1. **Insertion Sort** - Simple O(n²) algorithm, efficient for small/nearly sorted data
2. **Selection Sort** - O(n²) algorithm with minimal swaps
3. **Bubble Sort** - O(n²) algorithm with early termination optimization
4. **Quick Sort** - O(n log n) average case divide-and-conquer algorithm
5. **Heap Sort** - O(n log n) worst-case using max-heap structure
6. **Merge Sort** - O(n log n) stable sort using divide-and-conquer
7. **Radix Sort LSD** - O(n·k) non-comparison sort (Least Significant Digit)
8. **Radix Sort MSD** - O(n·k) non-comparison sort (Most Significant Digit)

## How to Build

\`\`\`bash
make compile
\`\`\`

This compiles all source files and creates the \`test\` executable.

## How to Run

### Run a specific sorting algorithm:

\`\`\`bash
./test <input_file> <algorithm_number> [bits_per_digit]
\`\`\`

**Algorithm numbers:**
- 0 = Insertion Sort
- 1 = Selection Sort
- 2 = Bubble Sort
- 3 = Quick Sort
- 4 = Heap Sort
- 5 = Merge Sort
- 6 = Radix Sort LSD (requires bits_per_digit parameter)
- 7 = Radix Sort MSD (requires bits_per_digit parameter)

**Example:**
\`\`\`bash
./test students-1000.txt 3          # Quick Sort
./test students-1000.txt 6 4        # Radix LSD with 4 bits per digit
\`\`\`

### Run all algorithms on all test files:

\`\`\`bash
make run
\`\`\`

This executes predefined test scenarios for each algorithm.

## Input File Format

Input files should contain student records in the format:
\`\`\`
<AEM_number> <Name>
\`\`\`

Example:
\`\`\`
1234 John_Smith
5678 Jane_Doe
\`\`\`

## Performance Metrics

When compiled with \`-D_PERF_\` flag (uncomment line in Makefile), the program outputs:
- Number of comparisons
- Number of copies/swaps
- Execution time in microseconds

## Known Issues

⚠️ **Critical Bug in test.c**: The switch statement for Radix Sort LSD (case 6) is missing a \`break\` statement, causing it to fall through and also execute Radix Sort MSD. This will produce incorrect results when running algorithm 6.

**Fix:** Add \`break;\` after the line with \`radixSortLSD(list, atoi(argv[3]));\` in test.c

## Cleaning Build Artifacts

\`\`\`bash
make clean
\`\`\`

Removes compiled object files and executables.

## Implementation Notes

- The doubly linked list provides O(1) insertion/removal at known positions
- Radix sorts require conversion to/from array representation
- Quick sort uses last element as pivot with in-place partitioning
- Heap sort builds max-heap then extracts elements
- All algorithms preserve the original comparison function for flexibility

## Requirements

- GCC compiler
- Make utility
- Math library (linked with \`-lm\` flag)
EOF
