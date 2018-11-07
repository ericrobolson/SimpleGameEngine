#ifndef SDLRECTANGLECOMPONENT_H
#define SDLRECTANGLECOMPONENT_H

#include "BaseComponent.h"


class SdlRectangleComponent : public BaseComponent
{
    public:
        SdlRectangleComponent();
        virtual ~SdlRectangleComponent();
        int Width;
        int Height;
        int Filled;
};

#endif // SDLRECTANGLECOMPONENT_H
