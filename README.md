# 🔗 NTU Algorithms PA2 – Maximum Planar Subset

## 📌 Project Title
**Maximum Planar Subset** – Programming Assignment 2 for NTU Algorithms (Fall 2024)

## 📄 Introduction

Given a set of chords in a circle (with no two sharing endpoints), this program computes the **Maximum Planar Subset (MPS)** — the largest set of chords such that no two intersect.

It uses a **dynamic programming** approach combined with traceback to reconstruct the optimal subset, ensuring high performance and memory efficiency even for large input sizes (up to 90,000 vertices).

## 📚 Table of Contents

- [Introduction](#-introduction)
- [Installation](#-installation)
- [Usage](#-usage)
- [Input Format](#-input-format)
- [Output Format](#-output-format)
- [Example](#-example)
- [Implementation Details](#-implementation-details)
- [File Structure](#-file-structure)
- [Compilation](#-compilation)
- [Performance](#-performance)
- [Troubleshooting](#-troubleshooting)
- [License](#-license)

## 🛠️ Installation

You must run this on a **Linux/Unix** system (e.g., EDA Union server at NTU).  
No external libraries are required.

## 🚀 Usage

```bash
./mps <input_file> <output_file>
```

### Example:
```bash
./mps 12.in 12.out
```

## 📥 Input Format

- A single integer `2n` representing the number of vertices (0 to 2n−1).
- `n` lines with two integers `a b` — endpoints of each chord.
- A final line containing `0`.

**Constraints**:
- 1 ≤ n ≤ 90,000
- 0 ≤ a, b < 2n
- No two chords share an endpoint.

**Sample Input (12.in):**
```
12
0 4
1 9
2 6
3 10
5 7
8 11
0
```

## 📤 Output Format

- First line: Number of chords in the maximum planar subset.
- Next lines: Each chord in the subset, sorted by the smaller endpoint.

**Sample Output (12.out):**
```
3
0 4
5 7
8 11
```

## ⚙️ Implementation Details

- **Language**: C++
- **Dynamic Programming**:
  - Memoization table stored as 1D upper-triangular matrix.
  - Complexity: O(n²)
- **Functions**:
  - `topdown(...)` — Computes optimal count.
  - `traceback(...)` — Reconstructs chord set.
  - `get1DIndex(...)` — Maps 2D DP to 1D vector.
  - `getMemoryUsage()` — [Optional] Linux memory monitor.
- **Output**:
  - Automatically writes to the output file.
  - Optional memory/time logging is available in the commented code.

## 📁 File Structure

```
<student_id>_pa2/
├── bin/
│   └── mps              # Compiled executable
├── doc/
│   └── report.pdf       # Algorithm explanation
├── src/
│   └── maxPlanarSubset.cpp
├── inputs/              # example inputs
├── outputs/             # folder holding results
├── makefile             # For building 'mps'
├── README               # This file
```

## 🧱 Compilation

```bash
make
```

It should generate the executable at:
```
bin/mps
```

## 📈 Performance

- Runtime tested up to 90,000 vertices.
- Efficient memory usage with 1D DP representation.
- Optional:
  - Use `chrono` for measuring runtime.
  - Use `getrusage()` for measuring memory.

## 🐛 Troubleshooting

| Problem                           | Solution                                      |
|----------------------------------|-----------------------------------------------|
| Segmentation fault (large input) | Ensure sufficient system memory (use EDA)     |
| Wrong result count               | Verify input format, especially final `0`     |
| Compilation error                | Ensure Linux + g++ with C++11 or later        |

## 🪪 License

This project is part of NTU’s Algorithms Course Fall 2024 and follows the academic integrity policy.  
Redistribution or reuse is prohibited without written permission.
