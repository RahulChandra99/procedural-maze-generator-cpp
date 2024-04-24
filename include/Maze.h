

#ifndef PROCGEN_BUILD_MAZE_H
#define PROCGEN_BUILD_MAZE_H

#include "NGLScene.h"
#include "Prims.h"
#include "Wilsons.h"
#include "DFSRecursive.h"

class Maze
{
public :
    static int myWidth;
    static int myDepth;
    static int map[100][100];
    static void Generate(int algoToRunValue);
    static void InitialiseMap();
    static std::vector<MapLocation> directions;



    static int CountSquareNeighbours(int x , int z);
    static int CountDiagonalNeighbours(int x , int z);
    static int CountAllNeighbours(int x , int z);
};



#endif //PROCGEN_BUILD_MAZE_H
