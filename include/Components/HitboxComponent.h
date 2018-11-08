#ifndef HITBOXCOMPONENT_H
#define HITBOXCOMPONENT_H

#include "BaseComponent.h"


class HitboxComponent : public BaseComponent
{
    public:
        HitboxComponent();
        virtual ~HitboxComponent();

        int SetHeight(int height);
        int SetWidth(int width);

        int GetHeight();
        int GetWidth();
    private:
        int _height;
        int _width;
};

#endif // FOOTPRINTCOMPONENT_H
