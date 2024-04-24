
#include <iostream>
#include "Maze.h"


int Maze::myWidth = 15;
int Maze::myDepth = 15;
int Maze::map[100][100];
std::vector<MapLocation> Maze::directions;

void Maze::InitialiseMap()
{
  std::srand(std::time(nullptr));

  for(int z = 0;z < myDepth; z++) {
    for (int x = 0; x < myWidth; x++)
    {
      map[x][z] = 1;       //1 = wall  0 = corridor
    }
  }
}

void Maze::Generate(int algoToRunValue)
{

  switch (algoToRunValue)
  {
    case 0:
      //Prim's Algorithm
      Prims::PrimsGenerate();
      break;
    case 1:
      //Wilson's Algorithm
      Wilsons::WilsonsGenerate();
      break;
    case 2:
      //DFS Recursive Backtracking Algorithm
      DFSRecursive::DFSGenerate();
  }

}

int Maze::CountSquareNeighbours(int x, int z)
{
  int count = 0;
  if ( x<= 0 || x >= myWidth - 1 || z <= 0 || z >= myDepth -1 ) return 5;

  if( map[x-1][z] == 0) count ++;
  if( map[x+1][z] == 0) count ++;
  if( map[x][z-1] == 0) count ++;
  if( map[x][z+1] == 0) count ++;

  return count;
}

int Maze::CountDiagonalNeighbours(int x, int z)
{
  int count = 0;
  if ( x<= 0 || x >= myWidth - 1 || z <= 0 || z >= myDepth -1 ) return 5;

  if( map[x-1][z-1] == 0) count ++;
  if( map[x+1][z+1] == 0) count ++;
  if( map[x+1][z-1] == 0) count ++;
  if( map[x-1][z+1] == 0) count ++;

  return count;
}

int Maze::CountAllNeighbours(int x , int z)
{
  return Maze::CountSquareNeighbours(x,z) + Maze::CountDiagonalNeighbours(x,z);
}
