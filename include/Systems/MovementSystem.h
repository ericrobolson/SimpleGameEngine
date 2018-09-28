#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "BaseSystem.h"
#include "EntityComponentManager.h"

class MovementSystem : public BaseSystem
{
    public:
        MovementSystem();
        virtual ~MovementSystem();
        bool Process(ECS::EntityComponentManager &ecs);
};

#endif // MOVEMENTSYSTEM_H
