// Copyright (c) 2018, Eric Olson
#include <SDL.h>
#include "Worlds/GameWorld.h"

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
