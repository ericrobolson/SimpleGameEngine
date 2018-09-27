#ifndef RECTANGLECOMPONENT_H
#define RECTANGLECOMPONENT_H

#include "BaseComponent.h"


class RectangleComponent : public BaseComponent
{
    public:
        RectangleComponent();
        virtual ~RectangleComponent();

        int Width = 0;
        int Height = 0;

    protected:

    private:
};

#endif // RECTANGLECOMPONENT_H
