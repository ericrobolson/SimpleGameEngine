#include "GameWorld.h"
#include <string>

GameWorld::GameWorld() : BaseWorld()
{
}

GameWorld::~GameWorld()
{
    //dtor
}

bool GameWorld::Process(){
    // Process the systems

    printf("\nGrapics system:");
    if (!_graphicsSystem.Process(_entities)){
        return false;
    }

    return true;
}
