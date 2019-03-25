#ifndef GRAPHICSSYSTEM_H
#define GRAPHICSSYSTEM_H
#include <SDL.h>
#include "BaseSystem.h"
#include "EntityComponentManager.h"
#include "BucketTree.h"
#include <mutex>

class GraphicsSystem : public BaseSystem
{
    public:
        GraphicsSystem();
        virtual ~GraphicsSystem();
        bool Process(ECS::EntityComponentManager &ecs, SGE_Physics::BucketTree& bucketTree);
        SDL_Renderer* GetRenderer();
        bool DrawHitboxes;
        bool DebugMode = true;
    private:
        void ProcessJob(ECS::EntityComponentManager &ecs, int entityId);
        std::mutex _resourceMutex;
        SDL_Window* _window;
        SDL_Renderer* _renderer;  // Holds rendering surface properties.
};

#endif // GRAPHICSSYSTEM_H
