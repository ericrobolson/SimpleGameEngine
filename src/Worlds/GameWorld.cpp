#include "GameWorld.h"
#include "InputState.h"
#include "PlayerAssemblage.h"


GameWorld::GameWorld() : BaseWorld()
{
    PlayerAssemblage::GeneratePlayer(entityComponentManager);
}

GameWorld::~GameWorld()
{
    //dtor
}

bool GameWorld::Process(){
    // Process the systems

    _inputSystem.Process(entityComponentManager);

    _movementSystem.Process(entityComponentManager);

    _graphicsSystem.Process(entityComponentManager);

    if (InputState::Instance().Exit == true){
        return false;
    }

    return true;
}
