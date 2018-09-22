#include "GraphicsSystem.h"
#include <SDL.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BITSPERPIXEL = 32;

// Initialize SDL
GraphicsSystem::GraphicsSystem() : BaseSystem()
{
    printf("Initializing SDL.\n");

    _exit = false;
    _window = nullptr;
    _renderer = nullptr;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else{

        _window = SDL_CreateWindow( "Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );


        if( _window == nullptr )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get window surface
            _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        }
    }
}

bool GraphicsSystem::Process(std::vector<std::shared_ptr<Entity>>& entities){

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT) {
            _exit = true;
        }

        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    _exit = true;
                    break;

            }


        }

    }


    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);  // Dark grey.
    SDL_RenderClear(_renderer);




    // Swap buffers.
    SDL_RenderPresent(_renderer);

    if (_exit == true){
        return false;
    }

    return true;
}


GraphicsSystem::~GraphicsSystem()
{
    // Cleanup SDL
    if (_renderer != nullptr){
            SDL_DestroyRenderer(_renderer);
    }

    if (_window != nullptr){
        SDL_DestroyWindow(_window);
        _window = nullptr;
    }

    SDL_Quit();
}
