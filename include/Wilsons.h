
#ifndef PROCGEN_BUILD_WILSONS_H
#define PROCGEN_BUILD_WILSONS_H

#include "Maze.h"
#include "MapLocation.h"


class Wilsons
{
public:
    static void WilsonsGenerate();
    static void RandomWalk();
    static int CountSquareMazeNeighbours(int x,int z);
    static int GetAvailableCells();

private:
    static std::vector<MapLocation> inWalk;
    static std::vector<MapLocation> notUsed;

};


#endif //PROCGEN_BUILD_WILSONS_H
