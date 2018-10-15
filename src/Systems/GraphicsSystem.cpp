#include <SDL.h>
#include <list>
#include "GraphicsSystem.h"
#include "EntityComponentManager.h"
#include "ColorComponent.h"
#include "RectangleComponent.h"
#include "PositionComponent.h"
#include "MovementComponent.h"
#include <math.h>
#include <future>
#include "ThreadPool.h"
#include "InputState.h"
#include "PlayerComponent.h"
#include <mutex>
#include "GameState.h"
#include "HexagonShape.h"

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int SCREEN_BITSPERPIXEL = 32;

bool IsOdd(int x){
    return x %2;
}

int GetScreenPositionXFromCoordinates(int x, int y){
    // returns x center of hex

    int screenX = x * GameState::HextileSize + GameState::HextileSize /2;

    if (IsOdd(y)){
        screenX += GameState::HextileSize /2;
    }

    return screenX;
}

int GetScreenPositionYFromCoordinates(int x, int y){
    // returns y center of hex
        // returns x center of hex
    int screenY = y * (GameState::HextileSize - GameState::HextileSize/4) + GameState::HextileSize/2;

    return screenY * GameState::IsometricScaling;
}

// Initialize SDL
GraphicsSystem::GraphicsSystem() : BaseSystem()
{
    std::unique_lock lock(_resourceMutex);
    if (SDL_WasInit(SDL_INIT_VIDEO) == 0){
        SDL_Init(SDL_INIT_VIDEO);
    }

    // Possibly move the renderer & window out to a static object, so there's only one? but then, why would we need more than one graphics system?
    _window = nullptr;
    _renderer = nullptr;

    _window = SDL_CreateWindow( "Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

    SDL_SetWindowFullscreen(_window,SDL_WINDOW_FULLSCREEN);


    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void GraphicsSystem::ProcessEntities(ECS::EntityComponentManager &ecs, int entityId){
    std::unique_lock lock(_resourceMutex);
    ecs.Lock();
    std::shared_ptr<ColorComponent> colorComponent = ecs.GetComponent<ColorComponent>(entityId);
    std::shared_ptr<RectangleComponent> rectangleComponent = ecs.GetComponent<RectangleComponent>(entityId);
    std::shared_ptr<PositionComponent> positionComponent = ecs.GetComponent<PositionComponent>(entityId);
    std::shared_ptr<MovementComponent> movementComponent = ecs.GetComponent<MovementComponent>(entityId);
    std::shared_ptr<PlayerComponent> playerComponent = ecs.GetComponent<PlayerComponent>(entityId);
    if (rectangleComponent != nullptr && positionComponent != nullptr){
        if (colorComponent != nullptr){
            SDL_SetRenderDrawColor(_renderer, colorComponent->Red, colorComponent->Green, colorComponent->Blue, colorComponent->Alpha);

        }
        SDL_Rect rectangle;
        rectangle.h = rectangleComponent->Height;
        rectangle.w = rectangleComponent->Width;
        rectangle.x = GetScreenPositionXFromCoordinates(positionComponent->PositionX, positionComponent->PositionY);
        rectangle.y = GetScreenPositionYFromCoordinates(positionComponent->PositionX, positionComponent->PositionY);

        SDL_RenderFillRect(_renderer, &rectangle);


    }

    if (movementComponent != nullptr && positionComponent != nullptr){
        int startX = positionComponent->PositionX;
        int startY = positionComponent->PositionY;

        int xDelta = cos(movementComponent->GetAngleInRadians()) * 100;
        int yDelta = sin(movementComponent->GetAngleInRadians()) * 100;

        SDL_RenderDrawLine(_renderer, startX, startY, startX + xDelta, startY + yDelta);
    }

    if (playerComponent != nullptr && positionComponent != nullptr){
        if (InputState::Instance().Button1IsPressed){

            int startX = positionComponent->PositionX;
            int startY = positionComponent->PositionY;
            SDL_RenderDrawLine(_renderer, startX, startY, InputState::Instance().CursorX, InputState::Instance().CursorY);

        }
    }

    ecs.Unlock();
}

void GraphicsSystem::DrawHexes(){
    std::unique_lock lock(_resourceMutex);

    HexagonShape hexagon;
    hexagon.hexRadius = GameState::HextileSize;
    hexagon.repeatable = true;

    // draw hexes
    for (int xIndex = -1; xIndex < GameState::MaxXTiles; xIndex++){
        for (int yIndex = -1; yIndex < GameState::MaxYTiles; yIndex++){
            int startX = GetScreenPositionXFromCoordinates(xIndex, yIndex);
            int startY = GetScreenPositionYFromCoordinates(xIndex, yIndex);

            hexagon.x = startX;
            hexagon.y = startY;
            hexagon.Render(_renderer);
        }
    }

    // outline hex around mouse
    int cursorX = InputState::Instance().CursorX / GameState::HextileSize;
    int cursorY = InputState::Instance().CursorY / (GameState::HextileSize - GameState::HextileSize/4) / GameState::IsometricScaling;

    // Add an additional offset to deal with odd number squares
    if (IsOdd(cursorY) && cursorX != 0){
        cursorX = (InputState::Instance().CursorX - GameState::HextileSize/2)/ GameState::HextileSize;
    }

    int startY = GetScreenPositionYFromCoordinates(cursorX, cursorY);
    int startX = GetScreenPositionXFromCoordinates(cursorX, cursorY);

    hexagon.LineColor.alpha = SDL_ALPHA_OPAQUE;
    hexagon.LineColor.red = 255;
    hexagon.LineColor.green = 255;
    hexagon.LineColor.blue = 255;

    hexagon.repeatable = false;
    hexagon.x = startX;
    hexagon.y = startY;
    hexagon.Render(_renderer);
}

bool GraphicsSystem::Process(ECS::EntityComponentManager &ecs){
    std::unique_lock lock(_resourceMutex);

    SDL_SetRenderDrawColor(_renderer, 34,139,34, 255);  // Dark green.
    SDL_RenderClear(_renderer);

    lock.unlock();

    ThreadPool::Instance().submit([this](){
                                        DrawHexes();
                                        });


    // Do component rendering??
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
    std::unique_lock lock(_resourceMutex);
    // Cleanup SDL
    if (_renderer != nullptr){
        SDL_DestroyRenderer(_renderer);
    }

    if (_window != nullptr){
        SDL_DestroyWindow(_window);
        _window = nullptr;
    }
}
