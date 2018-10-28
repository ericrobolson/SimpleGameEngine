#include <SDL.h>
#include <list>
#include "GraphicsSystem.h"
#include "EntityComponentManager.h"
#include "PositionComponent.h"
#include "MovementComponent.h"
#include <math.h>
#include <future>
#include "ThreadPool.h"
#include "InputState.h"
#include <mutex>
#include "GameState.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int SCREEN_BITSPERPIXEL = 32;

// Initialize SDL
GraphicsSystem::GraphicsSystem() : BaseSystem()
{
    std::unique_lock<std::mutex> lock(_resourceMutex);
    if (SDL_WasInit(SDL_INIT_VIDEO) == 0){
        SDL_Init(SDL_INIT_VIDEO);
    }

    // Possibly move the renderer & window out to a static object, so there's only one? but then, why would we need more than one graphics system?
    _window = nullptr;
    _renderer = nullptr;

    _window = SDL_CreateWindow( "Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void GraphicsSystem::ProcessEntities(ECS::EntityComponentManager &ecs, int entityId){
    std::unique_lock<std::mutex> lock(_resourceMutex);
}

bool GraphicsSystem::Process(ECS::EntityComponentManager &ecs){
    std::unique_lock<std::mutex> lock(_resourceMutex);

    SDL_SetRenderDrawColor(_renderer, 34,139,34, 255);  // Dark green.
    SDL_RenderClear(_renderer);

    lock.unlock();

    ThreadPool::Instance().submit([this](){
                                        });


    // Do component rendering??

/*
    ecs.Lock();

    std::vector<int> entityIds = ecs.Search<RectangleComponent>();
    ecs.Unlock();

    while (entityIds.empty() == false){
        int entityId = entityIds.back();
        entityIds.pop_back();

        ThreadPool::Instance().submit([this, &ecs, entityId](){
                                            ProcessEntities(ecs, entityId);
                                        });

    }
*/




    std::future<bool> isDone = ThreadPool::Instance().submit([](){

                                                        return true;
                                                        });

    isDone.get();

    // Swap buffers.
    lock.lock();
    SDL_RenderPresent(_renderer);


    return true;
}

GraphicsSystem::~GraphicsSystem()
{
    std::unique_lock<std::mutex> lock(_resourceMutex);
    // Cleanup SDL
    if (_renderer != nullptr){
        SDL_DestroyRenderer(_renderer);
    }

    if (_window != nullptr){
        SDL_DestroyWindow(_window);
        _window = nullptr;
    }
}
