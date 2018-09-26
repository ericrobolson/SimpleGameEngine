#include <SDL.h>
#include "InputSystem.h"
#include "InputState.h"
#include <string>
#include <iostream>
#include "EntityComponentManager.h"
#define DEBUG

void DebugMessage(std::string message){
    #ifdef DEBUG
        std::cout << "Debug: " << message << std::endl;
    #endif // DEBUG
}

InputSystem::InputSystem() : BaseSystem()
{
    if (SDL_WasInit(SDL_INIT_EVENTS) == 0){
        SDL_Init(SDL_INIT_EVENTS);
    }
    _exit = false;
}

bool InputSystem::Process(EntityComponentManager &ecs){
    InputState::Instance().Reset();

    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT) {
            InputState::Instance().Exit = true;
            _exit = true;

            DebugMessage("Exiting button pressed");
        }

        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    InputState::Instance().Exit = true;
                    _exit = true;
                    break;
                case SDLK_w:
                    InputState::Instance().ButtonUpIsPressed = true;
                    DebugMessage("Button Press: W");

                    break;
                case SDLK_a:
                    InputState::Instance().ButtonLeftIsPressed = true;
                    DebugMessage("Button Press: A");

                    break;
                case SDLK_s:
                    InputState::Instance().ButtonDownIsPressed = true;
                    DebugMessage("Button Press: S");

                    break;
                case SDLK_d:
                    InputState::Instance().ButtonRightIsPressed = true;
                    DebugMessage("Button Press: D");

                    break;
            }
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN){
            switch (event.button.button){
                case SDL_BUTTON_LEFT:
                    InputState::Instance().Button1IsPressed = true;
                    DebugMessage("Button Press: MbLeft");

                    break;
                case SDL_BUTTON_RIGHT:
                    InputState::Instance().Button2IsPressed = true;
                    DebugMessage("Button Press: MbRight");

                    break;
            }
        }
        else if (event.type == SDL_MOUSEMOTION){
            InputState::Instance().CursorX = event.motion.x;
            InputState::Instance().CursorY = event.motion.y;

            DebugMessage("MouseX: " + std::to_string(event.motion.x));
            DebugMessage("MouseY: " + std::to_string(event.motion.y));
        }
    }

    return !_exit;
}


InputSystem::~InputSystem()
{
    //dtor
}
