#ifndef GAMEWORLD_H
#define GAMEWORLD_H
#include <time.h>

#include "BaseWorld.h"
#include "GraphicsSystem_2dSdl.h"
#include "InputSystem.h"
#include "SystemTimer.h"
#include "PhysicsEngine.h"
#include "ActionSystem.h"
#include "BucketTree.h"
#include <memory>

class GameWorld_2d : public BaseWorld
{
    public:
        GameWorld_2d();
        virtual ~GameWorld_2d();
        virtual bool Process();

    private:
        GraphicsSystem_2dSdl _graphicsSystem;
        InputSystem _inputSystem;
        SGE_Physics::PhysicsEngine _physicsEngine;
        ActionSystem _actionSystem;

        std::shared_ptr<SGE_Physics::BucketTree> _bucketTree;

        clock_t _cycleClock;
        SystemTimer _systemTimer;
        SystemTimer _physicsTimer;
};

#endif // GAMEWORLD_H
