#include <SDL.h>
#include "InputSystem.h"
#include "InputState.h"
#include <string>
#include <iostream>
#include "EntityComponentManager.h"
#include "GameState.h"
#include "ThreadPool.h"
#include <future>

InputSystem::InputSystem() : BaseSystem()
{
    if (SDL_WasInit(SDL_INIT_EVENTS) == 0){
        SDL_Init(SDL_INIT_EVENTS);
    }
    _exit = false;
}

bool InputSystem::Process(ECS::EntityComponentManager &ecs){
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT) {
            InputState::Instance().Exit = true;
            _exit = true;
        }

        SDL_Keycode key = event.key.keysym.sym;

        if (event.type == SDL_KEYDOWN) {
            if (_keyMapper.Up == key){
                InputState::Instance().ButtonUpIsPressed = true;
            }else if (_keyMapper.Down == key){
                InputState::Instance().ButtonDownIsPressed = true;
            }else if (_keyMapper.Left == key){
                InputState::Instance().ButtonLeftIsPressed = true;
            }else if (_keyMapper.Right == key){
                InputState::Instance().ButtonRightIsPressed = true;
            }else if (_keyMapper.Pause == key){
                GameState::Instance().Paused = !GameState::Instance().Paused;
            }else if (_keyMapper.Escape == key){
                InputState::Instance().Exit = true;
                _exit = true;
            }
        }
         if (event.type == SDL_KEYUP) {
            if (_keyMapper.Up == key){
                InputState::Instance().ButtonUpIsPressed = false;
            }else if (_keyMapper.Down == key){
                InputState::Instance().ButtonDownIsPressed = false;
            }else if (_keyMapper.Left == key){
                InputState::Instance().ButtonLeftIsPressed = false;
            }else if (_keyMapper.Right == key){
                InputState::Instance().ButtonRightIsPressed = false;
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
        else if (event.type == SDL_MOUSEBUTTONUP){
            switch (event.button.button){
                case SDL_BUTTON_LEFT:
                    InputState::Instance().Button1IsPressed = false;
                    break;
                case SDL_BUTTON_RIGHT:
                    InputState::Instance().Button2IsPressed = false;
                    break;
            }
        }

        // Set the cursor position
        SDL_GetMouseState(&InputState::Instance().CursorX, &InputState::Instance().CursorY);
    }

    return !_exit;
}


InputSystem::~InputSystem()
{
    //dtor
}
