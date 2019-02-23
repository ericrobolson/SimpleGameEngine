#include "GameWorld.h"
#include "InputState.h"
#include <stdio.h>
#include <time.h>
#include <thread>
#include <memory>

#include <PlayerAssemblage.h>
#include "GameState.h"
#include "LevelLoader.h"
#include "SystemTimer.h"

#include "RandomNumberGenerator.h"

#include <iostream>

GameWorld::GameWorld() : BaseWorld()
{
    SGE::RandomNumberGenerator::Instance().Seed(3);

    _graphicsSystem.DrawHitboxes = true;

    _cycleClock = clock();

    LevelLoader loader;
    loader.LoadLevel("room_001", entityComponentManager);
}

GameWorld::~GameWorld()
{
    //dtor
}

bool GameWorld::Process(){
    if (_systemTimer.CanRun(60)){
        _inputSystem.Process(entityComponentManager);

      //  _networkSystem.Process(entityComponentManager);

        bool finishedProcessing = true;
        while(_graphicsSystem.Process(entityComponentManager) != finishedProcessing);

        if (InputState::Instance().Exit == true){
            return false;
        }

        _systemTimer.ResetClock();
    }

    return true;
}
