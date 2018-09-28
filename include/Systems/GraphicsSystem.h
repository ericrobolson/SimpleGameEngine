#ifndef GRAPHICSSYSTEM_H
#define GRAPHICSSYSTEM_H
#include <SDL.h>
#include "BaseSystem.h"
#include "EntityComponentManager.h"


class GraphicsSystem : public BaseSystem
{
    public:
        GraphicsSystem();
        virtual ~GraphicsSystem();
        bool Process(ECS::EntityComponentManager &ecs);

    private:
        SDL_Window* _window;
        SDL_Renderer* _renderer;  // Holds rendering surface properties.
};

#endif // GRAPHICSSYSTEM_H
