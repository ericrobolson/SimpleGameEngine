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

    if (!_inputSystem.Process(_entities)){
        return false;
    }

    if (!_graphicsSystem.Process(_entities)){
        return false;
    }

    return true;
}
