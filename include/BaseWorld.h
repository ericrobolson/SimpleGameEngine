#ifndef BASEWORLD_H
#define BASEWORLD_H
#include "EntityComponentManager.h"

class BaseWorld
{
    public:
        BaseWorld();
        virtual ~BaseWorld();
        virtual bool Process();
    protected:
        ECS::EntityComponentManager entityComponentManager;
};

#endif // BASEWORLD_H
