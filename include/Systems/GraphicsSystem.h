#ifndef GRAPHICSSYSTEM_H
#define GRAPHICSSYSTEM_H
#include <SDL.h>
#include "BaseSystem.h"


class GraphicsSystem : public BaseSystem
{
    public:
        GraphicsSystem();
        virtual ~GraphicsSystem();
        bool Process(std::vector<std::shared_ptr<Entity>>& entities);

    private:
        SDL_Window* _window;
        SDL_Renderer* _renderer;  // Holds rendering surface properties.
};

#endif // GRAPHICSSYSTEM_H
