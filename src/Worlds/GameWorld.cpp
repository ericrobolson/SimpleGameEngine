#include "GameWorld.h"
#include "InputState.h"

GameWorld::GameWorld() : BaseWorld()
{
}

GameWorld::~GameWorld()
{
    //dtor
}

bool GameWorld::Process(){
    // Process the systems

    _inputSystem.Process(_entities);

    _graphicsSystem.Process(_entities);

    if (InputState::Instance().Exit == true){
        return false;
    }

    return true;
}
