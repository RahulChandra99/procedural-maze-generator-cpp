

#include "Prims.h"

std::vector<MapLocation> Prims::walls;

void Prims::PrimsGenerate()
{

  int x = 2;
  int z = 2;

  Maze::map[x][z] = 0;

  walls.emplace_back(x + 2, z);
  walls.emplace_back(x - 1, z);
  walls.emplace_back(x, z + 1);
  walls.emplace_back(x, z - 1);

  int countloops = 0;

  while (!walls.empty() && countloops < 5000)
  {
    int rwall = std::rand() % walls.size();
    x = walls[rwall].x;
    z = walls[rwall].z;
    walls.erase(walls.begin() + rwall);

    if(Maze::CountSquareNeighbours(x,z) == 1)
    {
      Maze::map[x][z] = 0;
      walls.emplace_back(x + 1, z);
      walls.emplace_back(x - 1, z);
      walls.emplace_back(x, z + 1);
      walls.emplace_back(x, z - 1);
    }

    countloops++;
  }

}