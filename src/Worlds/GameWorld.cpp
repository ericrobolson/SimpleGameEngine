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
    /*
    //todo:
        figure out your ideal fps, e.g. 60fps. Then, that means you need to process 60 loops per second. 30 fps means 30 loops per second, etc.

        possibly make game systems run at 30fps, then gfx run at 60fps?
    */


    int fps = 60;

    float idealClock = (float)CLOCKS_PER_SEC / fps;

    clock_t deltaClock = clock() - _cycleClock;

    if (deltaClock < idealClock){
        return true;
    }

    clock_t oldClock = _cycleClock;
    _cycleClock = clock();

    // Process the systems

    clock_t cycleClock = clock();

    _inputSystem.Process(entityComponentManager);


    cycleClock = clock() - cycleClock;
    clock_t inputClock = cycleClock;

    cycleClock = clock();

    if (!GameState::Instance().Paused){
        _movementSystem.Process(entityComponentManager);
    }

    cycleClock = clock() - cycleClock;
    clock_t movementClock = cycleClock;
    cycleClock = clock();

    if (!GameState::Instance().Paused){
        _collisionSystem.Process(entityComponentManager);
        _positionSystem.Process(entityComponentManager);
    }


    cycleClock = clock() - cycleClock;
    clock_t positionClock = cycleClock;
    cycleClock = clock();

    // Run the graphics system until it's done processing; for instance, rendering all the frames of a move animation in a turn based game
    bool finishedProcessing = true;
    while(_graphicsSystem.Process(entityComponentManager) != finishedProcessing);

    cycleClock = clock() - cycleClock;
    clock_t gfxClock = cycleClock;

    printf("--- START LOOP ---\n");

    clock_t totalClock = inputClock + movementClock + positionClock + gfxClock;

    printf("FPS: %f\n", (float)idealClock/deltaClock * fps);
    printf("'Input' system: %f percent of load\n", ((float)inputClock)/totalClock);
    printf("'Movement' system: %f percent of load\n", ((float)movementClock)/totalClock);
    printf("'Position' system: %f percent of load\n", ((float)positionClock)/totalClock);
    printf("'GFX' system: %f percent of load\n", ((float)gfxClock)/totalClock);
    printf("---- END LOOP ----\n");


    if (InputState::Instance().Exit == true){
        return false;
    }

    return true;
}
