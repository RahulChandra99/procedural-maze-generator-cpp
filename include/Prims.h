

#ifndef PROCGEN_BUILD_PRIMS_H
#define PROCGEN_BUILD_PRIMS_H


#include "NGLScene.h"
#include "MapLocation.h"
#include "Maze.h"

class Prims
{
public:
    static void PrimsGenerate();
    static std::vector<MapLocation> walls;

private:
};


#endif //PROCGEN_BUILD_PRIMS_H
