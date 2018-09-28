#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "BaseWorld.h"
#include "GraphicsSystem.h"
#include "InputSystem.h"
#include "MovementSystem.h"

class GameWorld : public BaseWorld
{
    public:
        GameWorld();
        virtual ~GameWorld();
        virtual bool Process();

    private:
        GraphicsSystem _graphicsSystem;
        InputSystem _inputSystem;
        MovementSystem _movementSystem;

};

#endif // GAMEWORLD_H
