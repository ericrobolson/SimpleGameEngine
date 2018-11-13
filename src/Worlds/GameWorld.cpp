#include "GameWorld.h"
#include "InputState.h"
#include <stdio.h>
#include <time.h>
#include <thread>
#include <memory>

#include <MovementComponent.h>
#include <PositionComponent.h>
#include <HitboxComponent.h>
#include <ImpassibleComponent.h>
#include <PlayerAssemblage.h>
#include "GameState.h"
#include "LevelLoader.h"
#include "SystemTimer.h"


GameWorld::GameWorld() : BaseWorld()
{
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

        if (!GameState::Instance().Paused){
            _movementSystem.Process(entityComponentManager);
        }

        if (!GameState::Instance().Paused){
            _collisionSystem.Process(entityComponentManager);
            _positionSystem.Process(entityComponentManager);
        }


        bool finishedProcessing = true;
        while(_graphicsSystem.Process(entityComponentManager) != finishedProcessing);

        if (InputState::Instance().Exit == true){
            return false;
        }

        _systemTimer.ResetClock();
    }

    return true;
}
