#include "GameWorld.h"
#include "InputState.h"
#include "PlayerAssemblage.h"
#include "EnemyAssemblage.h"
#include <stdio.h>
#include <time.h>

GameWorld::GameWorld() : BaseWorld()
{
    PlayerAssemblage::GeneratePlayer(entityComponentManager);
    EnemyAssemblage::GenerateEnemy(entityComponentManager);
    _cycleClock = clock();
}

GameWorld::~GameWorld()
{
    //dtor
}

bool GameWorld::Process(){
    /*
    //todo:
        figure out your ideal fps, e.g. 60fps. Then, that means you need to process 60 loops per second. 30 fps means 30 loops per second, etc.


    */


    int fps = 100;

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

    _movementSystem.Process(entityComponentManager);

    cycleClock = clock() - cycleClock;
    clock_t movementClock = cycleClock;

    _positionSystem.Process(entityComponentManager);

    cycleClock = clock() - cycleClock;
    clock_t positionClock = cycleClock;

    _graphicsSystem.Process(entityComponentManager);

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
