#ifndef NETWORKSYSTEM_H
#define NETWORKSYSTEM_H

#include "BaseSystem.h"
#include "EntityComponentManager.h"
#include <memory>

class NetworkSystem : public BaseSystem
{
    public:
        NetworkSystem();
        virtual ~NetworkSystem();
        bool Process(ECS::EntityComponentManager &ecs);

    private:

};

#endif // NETWORKSYSTEM_H
