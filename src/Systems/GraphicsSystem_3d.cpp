#include "GraphicsSystem_3d.h"
#include "Debugger.h"


GraphicsSystem_3d::GraphicsSystem_3d()
{
    //ctor
}

GraphicsSystem_3d::~GraphicsSystem_3d()
{
    //dtor
}

bool GraphicsSystem_3d::Process(ECS::EntityComponentManager& ecs){
    SGE::Debugger::Instance().WriteMessage("yo");
    return true;

}
