#include <SDL.h>
#include "InputSystem.h"
#include "InputState.h"
#include <string>
#include <iostream>
#include "EntityComponentManager.h"
#include "GameState.h"
#include "ThreadPool.h"
#include <future>
#include <fstream>
#include "StringOperations.h"
#include "PlayerComponent.h"
#include "ActorComponent.h"

InputSystem::InputSystem() : BaseSystem()
{
    if (SDL_WasInit(SDL_INIT_EVENTS) == 0){
        SDL_Init(SDL_INIT_EVENTS);
    }
    _exit = false;

    // Load config file?
    std::ifstream file("config/config.json", std::ios::in);

    if (file.is_open()){
        const std::string keyboardUp = "keyboardUp";
        const std::string keyboardDown = "keyboardDown";
        const std::string keyboardLeft = "keyboardLeft";
        const std::string keyboardRight = "keyboardRight";
        const std::string keyboardQuit = "keyboardQuit";
        const std::string keyboardPause = "keyboardPause";

        // TODO: These keys
        const std::string keyboardNextCard = "keyboardNextCard";
        const std::string keyboardPreviousCard = "keyboardPreviousCard";
        const std::string keyboardUseCard = "keyboardUseCard";

        for(std::string line; getline(file, line);){
            if (line.length() > 0){
                // skip comments
                if (line[0] == '#'){
                    continue;
                }

                if (line.find(keyboardQuit) != std::string::npos){
                    _keyMapper.Escape = StringOperations::ParseIntegers(line);
                }else if (line.find(keyboardUp) != std::string::npos){
                    _keyMapper.Up = StringOperations::ParseIntegers(line);
                }else if (line.find(keyboardDown) != std::string::npos){
                    _keyMapper.Down = StringOperations::ParseIntegers(line);
                }else if (line.find(keyboardLeft) != std::string::npos){
                    _keyMapper.Left = StringOperations::ParseIntegers(line);
                }else if (line.find(keyboardRight) != std::string::npos){
                    _keyMapper.Right = StringOperations::ParseIntegers(line);
                }else if (line.find(keyboardPause) != std::string::npos){
                    _keyMapper.Pause = StringOperations::ParseIntegers(line);
                }
            }
        }

        file.close();
    }


}


void SetAction(bool buttonIsPressed, ActorComponent::ButtonState& button){
    if (buttonIsPressed){
        button = ActorComponent::ButtonState::Pressed;
    }else if (button == ActorComponent::ButtonState::Pressed){
        button = ActorComponent::ButtonState::Released;
    }else{
        button = ActorComponent::ButtonState::Empty;
    }
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
            }
            else if (_keyMapper.Pause == key){
                GameState::Instance().Paused = !GameState::Instance().Paused;
            }else if (_keyMapper.Escape == key){
                InputState::Instance().Exit = true;
                _exit = true;
            }else if (_keyMapper.Escape == key){
                InputState::Instance().Exit = true;
                _exit = true;
            }else if (key == SDLK_SPACE){
                InputState::Instance().Button1IsPressed = true;
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
            }else if (_keyMapper.NextCard == key){
                InputState::Instance().Button4IsPressed = false;
            }else if (_keyMapper.UseCard == key){
                InputState::Instance().Button5IsPressed = false;
            }else if (_keyMapper.PreviousCard == key){
                InputState::Instance().Button6IsPressed = false;
            }else if (key == SDLK_SPACE){
                InputState::Instance().Button1IsPressed = false;
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


    std::vector<int> matchingEntityIds = ecs.Search<PlayerComponent>();


    std::vector<int>::iterator it;
    for (it = matchingEntityIds.begin(); it != matchingEntityIds.end(); it++){
        std::shared_ptr<ActorComponent> actorComponent = ecs.GetComponent<ActorComponent>(*it);

        if (actorComponent == nullptr){
                    continue;
        }


        SetAction(InputState::Instance().ButtonDownIsPressed, actorComponent->LeftStick.DownButton);
        SetAction(InputState::Instance().ButtonUpIsPressed, actorComponent->LeftStick.UpButton);
        SetAction(InputState::Instance().ButtonLeftIsPressed, actorComponent->LeftStick.LeftButton);
        SetAction(InputState::Instance().ButtonRightIsPressed, actorComponent->LeftStick.RightButton);

        SetAction(InputState::Instance().Button1IsPressed, actorComponent->PrimaryButtons.AButton);
        SetAction(InputState::Instance().Button2IsPressed, actorComponent->PrimaryButtons.RTrigger);

    }

    return !_exit;
}


InputSystem::~InputSystem()
{
    //dtor
}
