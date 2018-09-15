#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "BaseWorld.h"


class GameWorld : public BaseWorld
{
    public:
        GameWorld();
        virtual ~GameWorld();

        void Process();

    protected:

    private:
};

#endif // GAMEWORLD_H
