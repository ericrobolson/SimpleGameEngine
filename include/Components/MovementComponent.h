#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

#include <BaseComponent.h>

class MovementComponent : public BaseComponent
{
    public:
        MovementComponent();
        virtual ~MovementComponent();

        int VerticalSpeed;
        int HorizontalSpeed; // Positive number for moving right, negative for moving left
};

#endif // MOVEMENTCOMPONENT_H
