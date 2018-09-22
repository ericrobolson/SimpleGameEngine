#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "BaseWorld.h"
#include "GraphicsSystem.h"
#include "InputSystem.h"

class GameWorld : public BaseWorld
{
    public:
        GameWorld();
        virtual ~GameWorld();
        virtual bool Process();

    private:
        GraphicsSystem _graphicsSystem;
        InputSystem _inputSystem;
};

#endif // GAMEWORLD_H
