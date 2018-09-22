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
    InputState::Instance().Reset();

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
                case SDLK_w:
                    InputState::Instance().ButtonUpIsPressed = true;
                    break;
                case SDLK_a:
                    InputState::Instance().ButtonLeftIsPressed = true;
                    break;
                case SDLK_s:
                    InputState::Instance().ButtonDownIsPressed = true;
                    break;
                case SDLK_d:
                    InputState::Instance().ButtonRightIsPressed = true;
                    break;
            }
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN){
            switch (event.button.button){
                case SDL_BUTTON_LEFT:
                    InputState::Instance().Button1IsPressed = true;
                    break;
                case SDL_BUTTON_RIGHT:
                    InputState::Instance().Button2IsPressed = true;
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
