#ifndef FOOTPRINTCOMPONENT_H
#define FOOTPRINTCOMPONENT_H

#include "BaseComponent.h"


class FootprintComponent : public BaseComponent
{
    public:
        FootprintComponent();
        virtual ~FootprintComponent();

        int Height;
        int Width;
};

#endif // FOOTPRINTCOMPONENT_H
