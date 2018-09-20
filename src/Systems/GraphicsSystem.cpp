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

    _window = nullptr;
    _screenSurface = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else{

        _window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( _window == nullptr )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get window surface
            _screenSurface = SDL_GetWindowSurface(_window);

            //Fill the surface white
            SDL_FillRect( _screenSurface, nullptr, SDL_MapRGB( _screenSurface->format, 0xFF, 0xFF, 0xFF ) );


        }
    }
}

bool GraphicsSystem::Process(std::vector<std::shared_ptr<Entity>>& entities){
    if (_window == nullptr){
        return false;
    }

    //Get window surface
    _screenSurface = SDL_GetWindowSurface(_window);

    if (_screenSurface != nullptr){
        //Fill the surface white
        SDL_FillRect( _screenSurface, nullptr, SDL_MapRGB( _screenSurface->format, 0xFF, 0xFF, 0xFF ) );
    }

    //Update the surface
    SDL_UpdateWindowSurface(_window);

    return true;
}


GraphicsSystem::~GraphicsSystem()
{
    // Cleanup SDL
    if (_window != nullptr){
        SDL_DestroyWindow(_window);
    }

    if (_screenSurface != nullptr){
        delete _screenSurface;
    }

    SDL_Quit();
}
