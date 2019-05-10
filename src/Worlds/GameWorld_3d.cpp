#include "GameWorld_3d.h"
#include "RandomNumberGenerator.h"
#include "InputState.h"

GameWorld_3d::GameWorld_3d() : BaseWorld()
{
    //ctor
    SGE_Math::RandomNumberGenerator::Instance().Seed(3);

    _cycleClock = clock();
}

GameWorld_3d::~GameWorld_3d()
{
    //dtor
}


bool GameWorld_3d::Process(){

    bool quitGame = !_inputSystem.Process(entityComponentManager);
    _actionSystem.Process(entityComponentManager);

    _graphicsSystem.Process(entityComponentManager);

    _systemTimer.ResetClock();


    if (quitGame){
            return false;
    }


    return true;
}
