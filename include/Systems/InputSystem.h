#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include "BaseSystem.h"
#include "EntityComponentManager.h"

class InputSystem : public BaseSystem
{
    public:
        InputSystem();
        virtual ~InputSystem();
        bool Process(ECS::EntityComponentManager &ecs);

    private:
        bool _exit;
};

#endif // INPUTSYSTEM_H
