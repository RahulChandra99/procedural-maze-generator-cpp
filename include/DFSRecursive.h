
#ifndef PROCGEN_BUILD_DFSRECURSIVE_H
#define PROCGEN_BUILD_DFSRECURSIVE_H

#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "Maze.h"

class DFSRecursive
{
public:
    static void DFSGenerate();
    static void shuffleDirections();
private:
    static void Generate(int x, int z);
};


#endif //PROCGEN_BUILD_DFSRECURSIVE_H
