#include <SDL.h>
#include "InputSystem.h"
#include "InputState.h"

InputSystem::InputSystem() : BaseSystem()
{
    if (SDL_WasInit(SDL_INIT_EVENTS) == 0){
        SDL_Init(SDL_INIT_EVENTS);
    }
    _exit = false;
}

bool InputSystem::Process(std::vector<std::shared_ptr<Entity>>& entities){
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT) {
            InputState::Instance().Exit = true;
            _exit = true;
        }

        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    InputState::Instance().Exit = true;
                    _exit = true;
                    break;
            }
        }
    }

    return !_exit;
}


InputSystem::~InputSystem()
{
    //dtor
}
