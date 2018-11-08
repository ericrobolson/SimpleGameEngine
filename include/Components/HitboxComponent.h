#ifndef HITBOXCOMPONENT_H
#define HITBOXCOMPONENT_H

#include "BaseComponent.h"


class HitboxComponent : public BaseComponent
{
    public:
        HitboxComponent();
        virtual ~HitboxComponent();

        int Height;
        int Width;
};

#endif // FOOTPRINTCOMPONENT_H
