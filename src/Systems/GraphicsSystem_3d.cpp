#include "GraphicsSystem_3d.h"
#include "Debugger.h"

GraphicsSystem_3d::GraphicsSystem_3d()
{

}

GraphicsSystem_3d::~GraphicsSystem_3d()
{
}



bool GraphicsSystem_3d::Process(ECS::EntityComponentManager& ecs){
    SGE::Debugger::Instance().WriteMessage("yo");
    DrawScene();
    return true;

}


void GraphicsSystem_3d::DrawScene(){

}
