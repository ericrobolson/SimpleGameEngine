#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

#include <BaseComponent.h>

class MovementComponent : public BaseComponent
{
    public:
        MovementComponent();
        virtual ~MovementComponent();

        float VerticalSpeed; // Change to Float. Value of 1 = 1 pixel, but this allows for gradual speedups/slowdowns

         // Change to Float. Value of 1 = 1 pixel, but this allows for gradual speedups/slowdowns
        float HorizontalSpeed; // Positive number for moving right, negative for moving left
};

#endif // MOVEMENTCOMPONENT_H
