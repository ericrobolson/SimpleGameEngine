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

    _inputSystem.Process(entityComponentManager);

    _graphicsSystem.Process(entityComponentManager);

    if (InputState::Instance().Exit == true){
        return false;
    }

    return true;
}
