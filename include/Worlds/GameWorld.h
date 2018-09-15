#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "BaseWorld.h"
#include "GraphicsSystem.h"


class GameWorld : public BaseWorld
{
    public:
        GameWorld();
        virtual ~GameWorld();

        void Process();

    protected:

    private:
        GraphicsSystem _graphicsSystem;

};

#endif // GAMEWORLD_H
