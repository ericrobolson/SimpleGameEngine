#include "BaseWorld.h"

BaseWorld::BaseWorld()
{
    //ctor
}

BaseWorld::~BaseWorld()
{
    //dtor
}

bool BaseWorld::Process(){
    // This is where systems are processed


    // Ideal system order:

        // InputSystem
        // CollisionSystem?
        // MovementSystem
        // DrawSystem
    return true;
}
