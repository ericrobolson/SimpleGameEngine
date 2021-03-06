#include <SDL.h>
#include <list>
#include "GraphicsSystem_2d.h"
#include "EntityComponentManager.h"
#include <math.h>
#include <future>
#include "ThreadPool.h"
#include "InputState.h"
#include <mutex>
#include "GameState.h"
#include "PhysicsBodyComponent.h"
#include "Debugger.h"
#include "EVector.h"
#include "Aabb.h"
const int SCREEN_WIDTH = 2560;
const int SCREEN_HEIGHT = 1440;

const int SCREEN_BITSPERPIXEL = 32;

// Initialize SDL
GraphicsSystem_2d::GraphicsSystem_2d() : BaseSystem()
{
    std::unique_lock<std::mutex> lock(_resourceMutex);
    if (SDL_WasInit(SDL_INIT_VIDEO) == 0){
        SDL_Init(SDL_INIT_VIDEO);
    }

    // Possibly move the renderer & window out to a static object, so there's only one? but then, why would we need more than one graphics system?
    _window = nullptr;
    _renderer = nullptr;

    _window = SDL_CreateWindow( "Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP );
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}



void GraphicsSystem_2d::ProcessJob(ECS::EntityComponentManager &ecs, int entityId){
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

void DrawBucketTree(SGE_Physics::BucketTree& bucketTree, SDL_Renderer* renderer){
    // draw children
    if (bucketTree.NeBucketTreePtr != nullptr){
        DrawBucketTree(*bucketTree.NeBucketTreePtr, renderer);
    }

    if (bucketTree.NwBucketTreePtr != nullptr){
        DrawBucketTree(*bucketTree.NwBucketTreePtr, renderer);
    }

    if (bucketTree.SeBucketTreePtr != nullptr){
        DrawBucketTree(*bucketTree.SeBucketTreePtr, renderer);
    }

    if (bucketTree.SwBucketTreePtr != nullptr){
        DrawBucketTree(*bucketTree.SwBucketTreePtr, renderer);
    }

    SDL_Rect sdlRect;

    SGE_Math::EVector minCoordinate, maxCoordinate;

    minCoordinate = bucketTree.GetMinCoordinate();
    maxCoordinate = bucketTree.GetMaxCoordinate();


    sdlRect.x = ((int)minCoordinate.X);
    sdlRect.y = ((int)minCoordinate.Y);

    int w = (int)(maxCoordinate.X - minCoordinate.X);
    int h = (int)(maxCoordinate.Y - minCoordinate.Y);

    sdlRect.w = (w);
    sdlRect.h = (h);

    // Only draw if no more children
    if (bucketTree.NeBucketTreePtr == nullptr && bucketTree.NwBucketTreePtr == nullptr && bucketTree.SwBucketTreePtr == nullptr && bucketTree.SeBucketTreePtr == nullptr){
        // If it has entities, fill in the rectangle
        if (bucketTree.HasEntities()){
            SDL_SetRenderDrawColor(renderer, 255,250,205, 75);  // #FFFACD, pale yellow


            SDL_RenderFillRect(renderer, &sdlRect);
        }else{
            SDL_SetRenderDrawColor(renderer, 255,250,205, 255);  // #FFFACD, pale yellow

            SDL_RenderDrawRect(renderer, &sdlRect);
        }
    }else{
        SDL_SetRenderDrawColor(renderer, 0,255,255, 255);  // #FFFACD, pale yellow
        SDL_RenderDrawRect(renderer, &sdlRect);

    }








}

// For interpolation:
// must be variable
// e.g. support interpolation at any frame rate higher than the physics engine one. From physicsHz + 1 to 144hz as that's max supported.
// e.g. support interpolation at any frame rate higher than the physics engine one. From physicsHz + 1 to 144hz as that's max supported.


bool GraphicsSystem_2d::Process(ECS::EntityComponentManager &ecs, SGE_Physics::BucketTree& bucketTree){
    std::unique_lock<std::mutex> lock(_resourceMutex);

    SDL_SetRenderDrawColor(_renderer, 34,139,34, 255);  // Dark green.
    SDL_RenderClear(_renderer);


    // if Debug mode
    if (true){
        // draw bucketTree and buckets
        DrawBucketTree(bucketTree, _renderer);
    }

    //todo: fix this up; use spatialHashMap
    std::vector<int> entityIds = ecs.Search<PhysicsBodyComponent>();
    while (entityIds.empty() == false){
            int entityId = entityIds.back();
            entityIds.pop_back();

            std::shared_ptr<PhysicsBodyComponent> body = ecs.GetComponent<PhysicsBodyComponent>(entityId);

            SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);

            std::vector<EVector> points = body->Body.GetPoints();

            int pointsToDraw = points.size() + 1;

            SDL_Point linePoints[pointsToDraw];



            // Draw each line on the shape
            for (int i = 0; i < points.size(); i++){
                EVector a = points[i];

                linePoints[i].x = (int)a.X;
                linePoints[i].y = (int)a.Y;
            }

            linePoints[pointsToDraw - 1].x = (int)points[0].X;
            linePoints[pointsToDraw - 1].y = (int)points[0].Y;

            SDL_RenderDrawLines(_renderer, linePoints, pointsToDraw);
        }


    lock.unlock();

    std::future<bool> isDone = ThreadPool::Instance().submit([](){
                                                        return true;
                                                        });
    isDone.get();

    // Swap buffers.
    lock.lock();
    SDL_RenderPresent(_renderer);

    return true;
}

GraphicsSystem_2d::~GraphicsSystem_2d()
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
