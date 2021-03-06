#ifndef BASESYSTEM_H
#define BASESYSTEM_H
#include "EntityComponentManager.h"
#include "SystemTimer.h"
class BaseSystem
{
    public:
        BaseSystem();
        virtual ~BaseSystem();

        virtual bool Process(ECS::EntityComponentManager &ecs);
};

#endif // BASESYSTEM_H
