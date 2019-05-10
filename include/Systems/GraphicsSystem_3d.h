#ifndef GRAPHICSSYSTEM_3D_H
#define GRAPHICSSYSTEM_3D_H


#include "EntityComponentManager.h"
#include "BaseSystem.h"


class GraphicsSystem_3d
{
    public:
        GraphicsSystem_3d();
        virtual ~GraphicsSystem_3d();
        bool Process(ECS::EntityComponentManager &ecs);


};

#endif // GRAPHICSSYSTEM_3D_H
