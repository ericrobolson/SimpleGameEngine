#ifndef GRAPHICSSYSTEM_H
#define GRAPHICSSYSTEM_H
#include <SDL.h>
#include "BaseSystem.h"
#include "EntityComponentManager.h"
#include "BucketTree.h"
#include <mutex>

#include <vector>

class GraphicsSystem_2dSdl : public BaseSystem
{
    public:
        GraphicsSystem_2dSdl();
        virtual ~GraphicsSystem_2dSdl();
        bool Process(ECS::EntityComponentManager &ecs, SGE_Physics::BucketTree& bucketTree);
    private:
        void ProcessJob(ECS::EntityComponentManager &ecs, int entityId);
        std::mutex _resourceMutex;
        SDL_Window* _window;
        SDL_Renderer* _renderer;  // Holds rendering surface properties.
};

#endif // GRAPHICSSYSTEM_H
