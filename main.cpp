// Copyright (c) 2018, Eric Olson
#include <SDL.h>
#include <chrono>
#include <thread>
#include <exception>
#include <iostream>

#include "Worlds/GameWorld_2d.h"
#include "Worlds/GameWorld_3d.h"
#include "ThreadPool.h"

#include "FixedPointInt.h"

using namespace std;

#ifdef UNIT_TESTING
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include <iostream>
#else

int main( int argc, char* args[] )
{
    ThreadPool::Instance();

    cout << 1.21_fp << endl;


    if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return 0;
    }


    GameWorld_2d gameWorld;
    //GameWorld_3d gameWorld;

    while(gameWorld.Process()){}

    SDL_Quit();

    return 0;
}


#endif // UNIT_TESTING

