#ifndef BASESYSTEM_H
#define BASESYSTEM_H
#include "Entity.h"

class BaseSystem
{
    public:
        BaseSystem();
        virtual ~BaseSystem();

        virtual void Process(std::vector<std::shared_ptr<Entity>>);
};

#endif // BASESYSTEM_H
