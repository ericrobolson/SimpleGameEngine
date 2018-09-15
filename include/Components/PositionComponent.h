#ifndef POSITIONCOMPONENT_H
#define POSITIONCOMPONENT_H

#include <BaseComponent.h>

class PositionComponent : public BaseComponent
{
    public:
        PositionComponent();
        virtual ~PositionComponent();

        unsigned int PositionX;
        unsigned int PositionY;
};

#endif // POSITIONCOMPONENT_H
