#ifndef GAMEWORLD_H
#define GAMEWORLD_H
#include <time.h>

#include "BaseWorld.h"
#include "GraphicsSystem.h"
#include "InputSystem.h"
#include "MovementSystem.h"
#include "PositionSystem.h"
#include "CollisionSystem.h"

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
        PositionSystem _positionSystem;
        CollisionSystem _collisionSystem;
        clock_t _cycleClock;

};

#endif // GAMEWORLD_H
