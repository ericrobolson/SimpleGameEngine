#ifndef BASESYSTEM_H
#define BASESYSTEM_H
#include "Entity.h"

class BaseSystem
{
    public:
        BaseSystem();
        virtual ~BaseSystem();

        virtual bool Process(std::vector<std::shared_ptr<Entity>>& entities);
};

#endif // BASESYSTEM_H
