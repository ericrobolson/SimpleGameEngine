#ifndef GAMEWORLD_3D_H
#define GAMEWORLD_3D_H
#include <time.h>

#include "BaseWorld.h"
#include "InputSystem.h"
#include "SystemTimer.h"
#include "ActionSystem.h"
#include "GraphicsSystem_3d.h"
#include <memory>


class GameWorld_3d  : public BaseWorld
{
    public:
        GameWorld_3d();
        virtual ~GameWorld_3d();
        virtual bool Process();

    protected:

    private:
        GraphicsSystem_3d _graphicsSystem;
        InputSystem _inputSystem;
        ActionSystem _actionSystem;

        clock_t _cycleClock;
        SystemTimer _systemTimer;
        SystemTimer _physicsTimer;
};

#endif // GAMEWORLD_3D_H
