
#include "DFSRecursive.h"


void DFSRecursive::DFSGenerate()
{
  Generate(3, 3);
}

void DFSRecursive::Generate(int x, int z)
{
  if(Maze::CountSquareNeighbours(x,z) >= 2) return;
  Maze::map[x][z] = 0;

  DFSRecursive::shuffleDirections();

  Generate(x + Maze::directions[0].x , z + Maze::directions[0].z);
  Generate(x + Maze::directions[1].x , z + Maze::directions[1].z);
  Generate(x + Maze::directions[2].x , z + Maze::directions[2].z);
  Generate(x + Maze::directions[3].x , z + Maze::directions[3].z);


}

void DFSRecursive::shuffleDirections()
{
  // Obtain a time-based seed
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

  // Create a random number generator
  std::default_random_engine engine(seed);

  // Shuffle the vector
  std::shuffle(Maze::directions.begin(), Maze::directions.end(), engine);
}

