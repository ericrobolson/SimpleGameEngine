#ifndef ACTIONSYSTEM_H
#define ACTIONSYSTEM_H
#include "BaseSystem.h"
#include "EntityComponentManager.h"

class ActionSystem : public BaseSystem
{
    public:
        ActionSystem();
        virtual ~ActionSystem();

        bool Process(ECS::EntityComponentManager &ecs);

    protected:

    private:
};

#endif // ACTIONSYSTEM_H
