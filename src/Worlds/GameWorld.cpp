#include "GameWorld.h"

GameWorld::GameWorld() : BaseWorld()
{
    //ctor
}

GameWorld::~GameWorld()
{
    //dtor
}

void GameWorld::Process(){
    // Process the systems
    _graphicsSystem.Process(_entities);
}
