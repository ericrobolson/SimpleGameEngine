#include <SDL.h>
#include "InputSystem.h"
#include "InputState.h"
#include <string>
#include <iostream>
#include "EntityComponentManager.h"
#include "PlayerAssemblage.h"

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
         if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
                case SDLK_w:
                    InputState::Instance().ButtonUpIsPressed = false;
                    break;
                case SDLK_a:
                    InputState::Instance().ButtonLeftIsPressed = false;
                    break;
                case SDLK_s:
                    InputState::Instance().ButtonDownIsPressed = false;
                    break;
                case SDLK_d:
                    InputState::Instance().ButtonRightIsPressed = false;
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
                    PlayerAssemblage::GeneratePlayer(ecs);
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
