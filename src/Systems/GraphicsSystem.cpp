#include <SDL.h>
#include "GraphicsSystem.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int SCREEN_BITSPERPIXEL = 32;

// Initialize SDL
GraphicsSystem::GraphicsSystem() : BaseSystem()
{
    if (SDL_WasInit(SDL_INIT_VIDEO) == 0){
        SDL_Init(SDL_INIT_VIDEO);
    }

    // Possibly move the renderer & window out to a static object, so there's only one? but then, why would we need more than one graphics system?
    _window = nullptr;
    _renderer = nullptr;

    _window = SDL_CreateWindow( "Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

bool GraphicsSystem::Process(std::vector<std::shared_ptr<Entity>>& entities){
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);  // Dark grey.
    SDL_RenderClear(_renderer);

    // Do component rendering??

    // Swap buffers.
    SDL_RenderPresent(_renderer);

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
}
