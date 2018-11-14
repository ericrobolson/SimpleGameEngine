#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include "BaseSystem.h"
#include "EntityComponentManager.h"
#include <SDL.h>
class InputSystem : public BaseSystem
{
    public:
        InputSystem();
        virtual ~InputSystem();
        bool Process(ECS::EntityComponentManager &ecs);

    private:
        class KeycodeMapper{
            public:
            KeycodeMapper(){
                Up = SDLK_UP;
                Down = SDLK_DOWN;
                Left = SDLK_LEFT;
                Right = SDLK_RIGHT;
                Pause = SDLK_PAUSE;
                Escape = SDLK_F4;
            };

            SDL_Keycode Up;
            SDL_Keycode Down;
            SDL_Keycode Left;
            SDL_Keycode Right;
            SDL_Keycode Pause;
            SDL_Keycode Escape;
        };

        KeycodeMapper _keyMapper;

        bool _exit;
};

#endif // INPUTSYSTEM_H
