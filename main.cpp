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
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return 0;
    }

    GameWorld gameWorld;

    while(gameWorld.Process()){}

    SDL_Quit();

    return 0;
}
