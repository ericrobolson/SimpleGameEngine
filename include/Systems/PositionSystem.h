#ifndef POSITIONSYSTEM_H
#define POSITIONSYSTEM_H

#include "BaseSystem.h"
#include "EntityComponentManager.h"

class PositionSystem : public BaseSystem
{
    public:
        PositionSystem();
        virtual ~PositionSystem();
        bool Process(ECS::EntityComponentManager &ecs);
};

#endif // POSITIONSYSTEM_H
