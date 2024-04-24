
# 3D Procedural Maze Generation Program

## Overall Idea

This program allows user to generate a maze procedurally based on input provided by the user.

### Abstract

Procedural maze generation refers to the automatic generation of maze 
structures by algorithms. Unlike a manual maze, a programmable maze 
is created by the program as it runs, offering an infinite variety 
of possibilities and complexity This process is the principles of 
computer science interesting applications, especially in the areas 
of algorithm design and graph theory.

### Elements of the program

1. Spawn maze procedurally based on the inputs provided by user
2. Generate maze using different algorithms.The chosen algorithm affects the maze's branching complexity, 
path length, and solution difficulty.
3. Generate different maze at runtime and explore the maze in different camera views.

### Algorithms Brief

1. Prim's Algorithm - Prim's algorithm is a greedy algorithm that starts with a single node and grows a maze by adding the lowest-cost edges that connect the maze to new nodes, one at a time.
2. Wilson's Algorithm - Wilson's algorithm for maze generation uses loop-erased random walks to create a uniform spanning tree, ensuring that all possible mazes are equally likely.
3. Depth-First Search (DFS) with Backtracking - DFS with backtracking is a classic recursive algorithm that carves paths in a maze by moving forward until it can't go any further, then backtracking until a new path is available.

### Class Design

![ClassDiagram](https://github.com/NCCA/ase-assignment-RahulChandra99/assets/60950973/69b5e09b-a544-4e39-8c89-5e63723f333b)


## Development Environment


- build system generator: [CMake](https://cmake.org/)
- build system: [Ninja](https://ninja-build.org/)
- compiler: [GCC 12.2.1 x86_64-redhat-linux](https://linux.die.net/man/1/gcc)
- Integrated Development Environment (IDE): [JetBrains CLion](https://www.jetbrains.com/clion/)
- C++ libraries:
    - NCCA Graphics library: [ngl](https://github.com/NCCA/NGL)
    - general-purpose: C++ Standard Library
    - automated testing: [Google Test](https://github.com/google/googletest)
    - graphical user interface (GUI): [Qt](https://www.qt.io/)
- package manager: [vcpkg](https://github.com/Microsoft/vcpkg)
- version control system (VCS): [Git](https://git-scm.com/)


## Building the program

To build and run the program use:

```
mkdir build
cd build
cmake -G Ninja ..
ninja
./ProcGenNGL
```
Or use IDE like JetBrains CLion.

## Reference

Bellot, V., Cautrès, M., Favreau, J-M., Gonzalez-Thauvin, M., Lafourcade, P., Le Cornec, K., Mosnier, B. & Rivière-Wekstein, S. (2021). How to generate perfect mazes? Information Sciences, 572, 444-459. https://doi.org/10.1016/j.ins.2021.03.022.

Ioannidis, P.L. (2016). Procedural Maze Generation. Bachelor Thesis. National and Kapodistrian University of Athens, School of Sciences, Department of Informatics and Telecommunications. Supervised by Stamatopoulos, P. (PDF)https://pergamos.lib.uoa.gr/uoa/dl/frontend/file/lib/default/data/1324569/theFile
