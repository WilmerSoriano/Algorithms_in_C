# More_C_Program

# C Programming: Algorithms & Core Concepts

This repository offers an in-depth exploration of my C programming skills, focusing on implementing classic algorithms to showcase my understanding of performance, memory management, and time complexity (Big O notation).

---

## 🚀 Overview

![Example](example.gif)


* **Algorithm Implementations**

  * Sorting (Merge Sort, Quick Sort, Heap Sort)
  * Searching (Binary Search, Hashing)
  * Graph Traversals (DFS, BFS)
* **Core C Concepts**

  * Pointers & Memory Management
  * Dynamic Allocation
  * Structs & Modular Design
  * File I/O

---

## 📋 Requirements

* A UNIX-like environment (Linux, macOS, WSL)
* **GCC** (GNU Compiler Collection) or **Clang**
* Basic terminal/shell skills

---

## 🛠️ Compile & Run

Since there’s no Makefile, compile each `.c` file manually.

### General Program

Assume you have a source file `program.c`:

```bash
# Compile
gcc program.c -o program

# Run
./program
```

If file algorithm uses multiple sources, list them all:

```bash
compile:
gcc main.c helper.c utils.c -o my_app

Run:
./my_app [arg1] [arg2]
```

### Merge Sort Example

The `MergeSort.c` file accepts a test data file as a command‑line argument and sorts its contents (least to greatest). (For Test cases look into folder: 0_Test_Cases)

```c
/* Merge Sort Example
   Usage: ./merge_sort <input_file>
   (Optional) To print the array before/after:
   gcc DPRINTARRAY MergeSort.c -o merge_sort
*/
```

```bash
# Compile without array printing
gcc MergeSort.c -o merge_sort

# Compile with PRINTARRAY enabled
gcc DPRINTARRAY MergeSort.c -o merge_sort

# Run
touch data.txt             # create or ensure your input file exists
echo "5 3 8 1 4" > data.txt
./merge_sort data.txt
```

Output shows sorted list; with `-DPRINTARRAY`, it’ll also display before-and-after states.

---

## 📈 Complexity & Analysis

Each algorithm’s source includes comments on:

* Time Complexity (best/avg/worst case)
* Space Complexity graph (.xlsx)
* Stability & In‑place characteristics

Refer to the top of each `.c` file for detailed Big O analysis.

---
## NOTE ⚠️

The Test Cases on the folder have a very long runtime, 
you may create your own data.txt for shorter runtime.


---
## Contact Info! 🚀
*Name: Wilmer Soriano
*Email: official_Wilmer.2020@outlook.com
