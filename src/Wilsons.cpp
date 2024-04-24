
#include <cstdlib>
#include "Wilsons.h"

std::vector<MapLocation> Wilsons::inWalk;
std::vector<MapLocation> Wilsons::notUsed;


void Wilsons::WilsonsGenerate()
{
  int x = std::rand() % (Maze::myWidth - 1) + 1;
  int z = std::rand() % (Maze::myDepth - 1) + 1;
  Maze::map[x][z] = 2;

  Maze::directions = {
    MapLocation(1, 0),
    MapLocation(0, 1),
    MapLocation(-1, 0),
    MapLocation(0, -1)
  };

  while(GetAvailableCells() > 1)
    RandomWalk();
}
int Wilsons::CountSquareMazeNeighbours(int x,int z)
{
  int count = 0;
  for(int d = 0; d < Maze::directions.size() ; d++)
  {
    int nx = x + Maze::directions[d].x;
    int nz = z + Maze::directions[d].z;
    if(Maze::map[nx][nz] == 2)
    {
      count++;
    }
  }

  return count;
}

int Wilsons :: GetAvailableCells()
{
  notUsed.clear();
  for( int z = 1; z < Maze::myDepth - 1; z ++)
  {
    for( int x = 1; x < Maze::myWidth - 1 ; x++)
    {
      if(CountSquareMazeNeighbours(x,z) == 0)
      {
        notUsed.emplace_back(MapLocation(x,z));
      }
    }
  }

  return notUsed.size();
}

void Wilsons::RandomWalk()
{
  int cx;
  int cz;
  int randStartIndex = std::rand() % notUsed.size();

  cx = notUsed[randStartIndex].x;
  cz = notUsed[randStartIndex].z;

  inWalk.emplace_back(cx,cz);

  int loop = 0;
  bool validPath = false;
  while(cx > 0 && cx < Maze::myWidth - 1 && cz > 0 && cz < Maze::myDepth - 1 && loop<5000 && !validPath)
  {
    Maze::map[cx][cz] = 0;
    if (CountSquareMazeNeighbours(cx, cz) > 1)
      break;

    int randDir = std::rand() % Maze::directions.size();
    int nx = cx + Maze::directions[randDir].x;
    int nz = cz + Maze::directions[randDir].z;
    if(Maze::CountSquareNeighbours(nx,nz) < 2)
    {
      cx = nx;
      cz = nz;
      inWalk.emplace_back(cx,cz);
    }
    validPath = CountSquareMazeNeighbours(cx,cz) == 1;

    loop++;
  }

  if(validPath)
  {
    Maze::map[cx][cz] = 0;

    for(const MapLocation& m : inWalk)
    {
      Maze::map[m.x][m.z] = 2;
    }
    inWalk.clear();
  }
  else
  {
    for(const MapLocation& m : inWalk)
    {
      Maze::map[m.x][m.z] = 1;
    }
    inWalk.clear();
  }
}