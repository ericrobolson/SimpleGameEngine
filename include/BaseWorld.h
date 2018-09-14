#ifndef BASEWORLD_H
#define BASEWORLD_H
#include <vector>
#include <memory>
#include "Entity.h"

class BaseWorld
{
    public:
        BaseWorld();
        virtual ~BaseWorld();
        virtual void Process();

    private:
        std::vector<std::shared_ptr<Entity>> _entities;
};

#endif // BASEWORLD_H
