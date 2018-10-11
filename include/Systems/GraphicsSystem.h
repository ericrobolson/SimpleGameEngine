#ifndef GRAPHICSSYSTEM_H
#define GRAPHICSSYSTEM_H
#include <SDL.h>
#include "BaseSystem.h"
#include "EntityComponentManager.h"
#include <mutex>

class GraphicsSystem : public BaseSystem
{
    public:
        GraphicsSystem();
        virtual ~GraphicsSystem();
        bool Process(ECS::EntityComponentManager &ecs);
        SDL_Renderer* GetRenderer();
    private:
        void ProcessEntities(ECS::EntityComponentManager &ecs, int entityId);
        void DrawHexes();
        std::mutex _resourceMutex;
        SDL_Window* _window;
        SDL_Renderer* _renderer;  // Holds rendering surface properties.
};

#endif // GRAPHICSSYSTEM_H
