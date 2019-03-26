#ifndef PLAYERASSEMBLAGE_H
#define PLAYERASSEMBLAGE_H

#include <memory>
#include "EntityComponentManager.h"
#include "FixedPointInt.h"
class PlayerAssemblage
{
    public:
        PlayerAssemblage();
        virtual ~PlayerAssemblage();

        static std::shared_ptr<int> BuildPlayer(ECS::EntityComponentManager &ecs, SGE_Math::FixedPointInt x, SGE_Math::FixedPointInt y);

    protected:

    private:
};

#endif // PLAYERASSEMBLAGE_H
