#ifndef BASEWORLD_H
#define BASEWORLD_H
#include "EntityComponentManager.h"

class BaseWorld
{
    public:
        BaseWorld();
        virtual ~BaseWorld();
        virtual bool Process();

        ECS::EntityComponentManager entityComponentManager;
};

#endif // BASEWORLD_H
