#ifndef PLAYERASSEMBLAGE_H
#define PLAYERASSEMBLAGE_H

#include <memory>
#include "EntityComponentManager.h"
class PlayerAssemblage
{
    public:
        PlayerAssemblage();
        virtual ~PlayerAssemblage();

        static std::shared_ptr<int> BuildPlayer(ECS::EntityComponentManager &ecs, int x, int y);

    protected:

    private:
};

#endif // PLAYERASSEMBLAGE_H
