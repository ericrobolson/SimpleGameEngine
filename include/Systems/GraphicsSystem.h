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

    protected:

    private:
        SDL_Window* _window;
        SDL_Surface* _screenSurface;
};

#endif // GRAPHICSSYSTEM_H
