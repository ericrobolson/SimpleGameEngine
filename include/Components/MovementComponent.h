#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

#include <BaseComponent.h>

class MovementComponent : public BaseComponent
{
    public:
        MovementComponent();
        virtual ~MovementComponent();

        enum MovementDirections {
            NOTMOVING,
            UP,
            DOWN,
            LEFT,
            RIGHT
        };

        MovementDirections Direction;
        int Speed;

    protected:

    private:
};

#endif // MOVEMENTCOMPONENT_H
