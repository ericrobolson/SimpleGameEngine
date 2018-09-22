// Copyright (c) 2018, Eric Olson

#include "Entity.h"
#include "Components/PositionComponent.h"
#include "Components/MovementComponent.h"
#include "Worlds/GameWorld.h"

#include <iostream>
#include <memory>
#include <typeinfo>
#include <vector>
#include <SDL.h>



using namespace std;


int main( int argc, char* args[] )
{
    GameWorld gameWorld;

    while(gameWorld.Process()){}

    return 0;
}
