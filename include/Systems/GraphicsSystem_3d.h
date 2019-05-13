#ifndef GRAPHICSSYSTEM_3D_H
#define GRAPHICSSYSTEM_3D_H

#include "EntityComponentManager.h"
#include "BaseSystem.h"
#include <mutex>


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

        std::mutex _resourceMutex;
        SDL_Window* _window;
        SDL_Renderer* _renderer;  // Holds rendering surface properties.


};

#endif // GRAPHICSSYSTEM_3D_H
