#ifndef GRAPHICSSYSTEM_3D_H
#define GRAPHICSSYSTEM_3D_H

#include "EntityComponentManager.h"
#include "BaseSystem.h"

#include <SDL.h>
//#include <SDL_opengl.h>
//#include <SDL_opengles2.h>

class GraphicsSystem_3d
{
    public:
        GraphicsSystem_3d();
        virtual ~GraphicsSystem_3d();
        bool Process(ECS::EntityComponentManager &ecs);
    private:
        void DrawScene();

};

#endif // GRAPHICSSYSTEM_3D_H
