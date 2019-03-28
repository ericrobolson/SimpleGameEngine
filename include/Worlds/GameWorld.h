#ifndef GAMEWORLD_H
#define GAMEWORLD_H
#include <time.h>

#include "BaseWorld.h"
#include "GraphicsSystem.h"
#include "InputSystem.h"
#include "SystemTimer.h"
#include "PhysicsEngine.h"
#include "ActionSystem.h"
#include "BucketTree.h"
#include <memory>

class GameWorld : public BaseWorld
{
    public:
        GameWorld();
        virtual ~GameWorld();
        virtual bool Process();

    private:
        GraphicsSystem _graphicsSystem;
        InputSystem _inputSystem;
        SGE_Physics::PhysicsEngine _physicsEngine;
        ActionSystem _actionSystem;

        std::shared_ptr<SGE_Physics::BucketTree> _bucketTree;

        clock_t _cycleClock;
        SystemTimer _systemTimer;
        SystemTimer _physicsTimer;
};

#endif // GAMEWORLD_H
