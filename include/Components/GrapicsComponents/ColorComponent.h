#ifndef COLORCOMPONENT_H
#define COLORCOMPONENT_H
#include <cstdint>
#include <SDL.h>
#include "BaseComponent.h"


class ColorComponent : public BaseComponent
{
    public:
        ColorComponent();
        virtual ~ColorComponent();

        uint8_t Red = 0;
        uint8_t Green = 0;
        uint8_t Blue = 0;
        uint8_t Alpha = SDL_ALPHA_OPAQUE;

    protected:

    private:
};

#endif // COLORCOMPONENT_H
