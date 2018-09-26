#ifndef BASESYSTEM_H
#define BASESYSTEM_H
#include "EntityComponentManager.h"

class BaseSystem
{
    public:
        BaseSystem();
        virtual ~BaseSystem();

        virtual bool Process(EntityComponentManager &ecs);
};

#endif // BASESYSTEM_H
