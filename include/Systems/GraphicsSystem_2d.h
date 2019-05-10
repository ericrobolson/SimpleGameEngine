#ifndef GRAPHICSSYSTEM_H
#define GRAPHICSSYSTEM_H
#include <SDL.h>
#include "BaseSystem.h"
#include "EntityComponentManager.h"
#include "BucketTree.h"
#include <mutex>

#include <vector>

class GraphicsSystem_2d : public BaseSystem
{
    public:
        GraphicsSystem_2d();
        virtual ~GraphicsSystem_2d();
        bool Process(ECS::EntityComponentManager &ecs, SGE_Physics::BucketTree& bucketTree);
    private:
        void ProcessJob(ECS::EntityComponentManager &ecs, int entityId);
        std::mutex _resourceMutex;
        SDL_Window* _window;
        SDL_Renderer* _renderer;  // Holds rendering surface properties.
};

#endif // GRAPHICSSYSTEM_H
