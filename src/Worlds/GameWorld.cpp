#include "GameWorld.h"
#include "PlayerAssemblage.h"

GameWorld::GameWorld() : BaseWorld()
{
    AddEntity(PlayerAssemblage::CreatePlayerEntity());
}

GameWorld::~GameWorld()
{
    //dtor
}

void GameWorld::Process(){
    // Process the systems
    _graphicsSystem.Process(_entities);
}
