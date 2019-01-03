#include "BasicMaze.h"
#include "RandomNumberGenerator.h"
#include "Debugger.h"
#include <cstdlib>
using namespace std;
using namespace SGE;

BasicMaze::BasicMaze(){
    Reset();
}

BasicMaze::~BasicMaze()
{
    //dtor
}

void BasicMaze::SetMaze(bool value){
      for (int i = 0; i < MaxGridSize; i++){
        for (int j = 0; j < MaxGridSize; j++){
            _grid[i][j] = value;
        }
    }
}

void BasicMaze::Reset(){
    SetMaze(false);
}

void BasicMaze::Generate(){
    RandomNumberGenerator& rng = RandomNumberGenerator::Instance();

    CarvePath(rng.RandomInt(0, MaxGridSize), rng.RandomInt(0, MaxGridSize), 50);
}

void BoundsCheck(int& i){
    if (i < 0){
        i = 0;
    }

    if (i >= BasicMaze::MaxGridSize){
        i = BasicMaze::MaxGridSize-1;
    }
}

void BasicMaze::CarvePath(int x, int y, int length){
    BoundsCheck(x);
    BoundsCheck(y);

    if (length <= 0){
        return;
    }

    _grid[x][y] = true;


    // do some stuff
        // set next point, musut connect current point

    int nextX = x;
    int nextY = y;

    // Select a random direction to go next
    int dir = RandomNumberGenerator::Instance().RandomInt(0,4);

    switch(dir){
        // North
        case 0:
            if (!Occupied(x, y-1) && !Occupied(x, y-2)){
                nextY = y-1;
            }
            break;
        // South
        case 1:
            if (!Occupied(x, y+1) && !Occupied(x, y+2)){
                nextY = y+1;
            }
            break;
        // East
        case 2:
            if (!Occupied(x+1, y) && !Occupied(x+2, y)){
                nextX = x+1;
            }
            break;
        // West
        case 3:
            if (!Occupied(x-1, y) && !Occupied(x-2, y)){
                nextX = x-1;
            }
            break;
    }





    CarvePath(nextX, nextY, length -1);
}


bool BasicMaze::Occupied(int x, int y){


    return _grid[x][y];
}
