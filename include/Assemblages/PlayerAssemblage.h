#ifndef PLAYERASSEMBLAGE_H
#define PLAYERASSEMBLAGE_H
#include "EntityComponentManager.h"

class PlayerAssemblage
{
    public:
        PlayerAssemblage();
        virtual ~PlayerAssemblage();

        static int GeneratePlayer(EntityComponentManager &ec);

    protected:

    private:
};

#endif // PLAYERASSEMBLAGE_H
