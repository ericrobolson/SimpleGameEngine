#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include "BaseSystem.h"


class InputSystem : public BaseSystem
{
    public:
        InputSystem();
        virtual ~InputSystem();
        bool Process(std::vector<std::shared_ptr<Entity>>& entities);

    private:
        bool _exit;
};

#endif // INPUTSYSTEM_H
