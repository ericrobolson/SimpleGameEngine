#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "BaseSystem.h"
#include "EntityComponentManager.h"


class CollisionSystem : public BaseSystem
{
    public:
        CollisionSystem();
        virtual ~CollisionSystem();

        bool Process(ECS::EntityComponentManager &ecs);
};

#endif // COLLISIONSYSTEM_H
