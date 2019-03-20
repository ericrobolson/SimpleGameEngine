#include <SDL.h>
#include <list>
#include "GraphicsSystem.h"
#include "EntityComponentManager.h"
#include <math.h>
#include <future>
#include "ThreadPool.h"
#include "InputState.h"
#include <mutex>
#include "GameState.h"
#include "PhysicsBodyComponent.h"
#include "Debugger.h"
const int SCREEN_WIDTH = 800;
const int SCREEN_BITSPERPIXEL = 32;
const int SCREEN_HEIGHT = 600;

int ScaleGraphics(int value){
    return GameState::GfxScaling * value;
}

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



void GraphicsSystem::ProcessJob(ECS::EntityComponentManager &ecs, int entityId){
    std::unique_lock<std::mutex> lock(_resourceMutex);

    /*
    std::shared_ptr<PositionComponent> positionPtr = ecs.GetComponent<PositionComponent>(entityId);

    // Draw Hitboxes
    if (DrawHitboxes){
        std::shared_ptr<HitboxComponent> rectanglePtr = ecs.GetComponent<HitboxComponent>(entityId);
        if (rectanglePtr != nullptr && positionPtr != nullptr){
            SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);

            HitboxComponent rectangle = *rectanglePtr.get();
            PositionComponent position = *positionPtr.get();

            SDL_Rect sdlRect;

            sdlRect.x = ScaleGraphics(position.PositionX);
            sdlRect.y = ScaleGraphics(position.PositionY);
            sdlRect.w = ScaleGraphics(rectangle.GetWidth());
            sdlRect.h = ScaleGraphics(rectangle.GetHeight());

            SDL_RenderDrawRect(_renderer, &sdlRect);
        }
    }
    */
}

bool GraphicsSystem::Process(ECS::EntityComponentManager &ecs){
    std::unique_lock<std::mutex> lock(_resourceMutex);

    SDL_SetRenderDrawColor(_renderer, 34,139,34, 255);  // Dark green.
    SDL_RenderClear(_renderer);

    //todo: fix this up; use spatialHashMap
    std::vector<int> entityIds = ecs.Search<PhysicsBodyComponent>();
    while (entityIds.empty() == false){
            int entityId = entityIds.back();
            entityIds.pop_back();

            std::shared_ptr<PhysicsBodyComponent> body = ecs.GetComponent<PhysicsBodyComponent>(entityId);

            SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);


            SDL_Rect sdlRect;

            sdlRect.x = ((int)body->Body.Transform.Position.X);
            sdlRect.y = ((int)body->Body.Transform.Position.Y);

            int w = (int)body->Body.Shape.GetAabb().HalfWidth * 2;
            int h = (int)body->Body.Shape.GetAabb().HalfHeight * 2;

            sdlRect.w = (w);
            sdlRect.h = (h);

            SDL_RenderDrawRect(_renderer, &sdlRect);


           // ThreadPool::Instance().submit([this, &ecs, entityId](){
           //                                     ProcessJob(ecs, entityId);
           //                                 });
        }


    lock.unlock();

    /*
    std::vector<int> entityIds = ecs.Search<VisibleComponent>(); // change to visible component?

    while (entityIds.empty() == false){
        int entityId = entityIds.back();
        entityIds.pop_back();

        ThreadPool::Instance().submit([this, &ecs, entityId](){
                                            ProcessJob(ecs, entityId);
                                        });
    }
*/
    std::future<bool> isDone = ThreadPool::Instance().submit([](){
                                                        return true;
                                                        });
    isDone.get();

    // Draw maze
    lock.lock();



    lock.unlock();



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
