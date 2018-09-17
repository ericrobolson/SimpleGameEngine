#ifndef STATICSPRITECOMPONENT_H
#define STATICSPRITECOMPONENT_H

#include "BaseComponent.h"


class StaticSpriteComponent : public BaseComponent
{
    public:
        StaticSpriteComponent();
        virtual ~StaticSpriteComponent();

        double GetRotation();
        double SetRotation(double angle);
        int ZIndex;

    protected:
        double _rotation;
};

#endif // STATICSPRITECOMPONENT_H
