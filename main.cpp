// Copyright (c) 2018, Eric Olson
#include <SDL.h>
#include <chrono>
#include <thread>
#include <exception>
#include <iostream>

#include "Worlds/GameWorld.h"
#include "ThreadPool.h"
using namespace std;

#ifdef UNIT_TESTING
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include <iostream>
#else

int main( int argc, char* args[] )
{
    ThreadPool::Instance();

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return 0;
    }

    GameWorld gameWorld;

    while(gameWorld.Process()){}



    SDL_Quit();

    return 0;
}


#endif // UNIT_TESTING

