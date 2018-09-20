#include "GameWorld.h"
#include "PlayerAssemblage.h"
#include <string>

GameWorld::GameWorld() : BaseWorld()
{
    printf("Initializing GameWorld.\n");
//    AddEntity(PlayerAssemblage::CreatePlayerEntity());
    printf("Do player assemblage");
}

GameWorld::~GameWorld()
{
    //dtor
}

bool GameWorld::Process(){
    // Process the systems
    if (!_graphicsSystem.Process(_entities)){
        return false;
    }

    return true;
}
