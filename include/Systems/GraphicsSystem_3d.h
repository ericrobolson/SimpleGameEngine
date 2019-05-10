#ifndef GRAPHICSSYSTEM_3D_H
#define GRAPHICSSYSTEM_3D_H


#include "EntityComponentManager.h"
#include "BaseSystem.h"
#define GL_GLEXT_PROTOTYPES


#include <SDL.h>
#include <SDL_opengl.h>

class GraphicsSystem_3d
{
    public:
        GraphicsSystem_3d();
        virtual ~GraphicsSystem_3d();
        bool Process(ECS::EntityComponentManager &ecs);
    private:
        void DrawScrene();

        SDL_Window* _sdlWindow;
        SDL_GLContext* _glContext;
        GLuint _vao, _vbo;

};

#endif // GRAPHICSSYSTEM_3D_H
