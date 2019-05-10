#ifndef GAMEWORLD_H
#define GAMEWORLD_H
#include <time.h>

#include "BaseWorld.h"
#include "GraphicsSystem_2d.h"
#include "InputSystem.h"
#include "SystemTimer.h"
#include "PhysicsEngine.h"
#include "ActionSystem.h"
#include "BucketTree.h"
#include "NetworkSystem.h"
#include <memory>

class GameWorld_2d : public BaseWorld
{
    public:
        GameWorld_2d();
        virtual ~GameWorld_2d();
        virtual bool Process();

    private:
        GraphicsSystem_2d _graphicsSystem;
        InputSystem _inputSystem;
        SGE_Physics::PhysicsEngine _physicsEngine;
        ActionSystem _actionSystem;
        NetworkSystem _networkSystem;

        std::shared_ptr<SGE_Physics::BucketTree> _bucketTree;

        clock_t _cycleClock;
        SystemTimer _systemTimer;
        SystemTimer _gfxTimer;
        SystemTimer _physicsTimer;

        FixedPointInt _gfxHz = 144.0_fp; // 144 as that's my max. But, otherwise is configurable
        FixedPointInt _physicsHz = 60.0_fp; // run physics at either 45 or 60 hz, based on what feel you want
        FixedPointInt _systemHz = 30.0_fp; // run input, actions, resolutions and networking all at the same time so as to prevent desync issues.
};

#endif // GAMEWORLD_H
