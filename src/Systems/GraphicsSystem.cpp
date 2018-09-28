#include <SDL.h>
#include <list>
#include <iostream>
#include "GraphicsSystem.h"
#include "EntityComponentManager.h"
#include "ColorComponent.h"
#include "RectangleComponent.h"
#include "PositionComponent.h"

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

bool GraphicsSystem::Process(ECS::EntityComponentManager &ecs){
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);  // Dark grey.
    SDL_RenderClear(_renderer);

    // Do component rendering??

    std::list<int> entityIds = ecs.Search<RectangleComponent>();
    entityIds = ecs.Search<PositionComponent>(entityIds);

    while (entityIds.empty() == false){
        int entityId = entityIds.front();
        entityIds.pop_front();

        std::shared_ptr<ColorComponent> colorComponent = ecs.GetComponent<ColorComponent>(entityId);
        std::shared_ptr<RectangleComponent> rectangleComponent = ecs.GetComponent<RectangleComponent>(entityId);
        std::shared_ptr<PositionComponent> positionComponent = ecs.GetComponent<PositionComponent>(entityId);

        if (rectangleComponent != nullptr && positionComponent != nullptr){
            if (colorComponent != nullptr){
                SDL_SetRenderDrawColor(_renderer, colorComponent->Red, colorComponent->Green, colorComponent->Blue, colorComponent->Alpha);
            }
            SDL_Rect rectangle;
            rectangle.h = rectangleComponent->Height;
            rectangle.w = rectangleComponent->Width;
            rectangle.x = positionComponent->PositionX;
            rectangle.y = positionComponent->PositionY;

            std::cout << std::endl << "Rectangle X: " << rectangleComponent->Height << " Y: " << rectangle.y << std::endl;

            SDL_RenderFillRect(_renderer, &rectangle);
        }
    }





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
