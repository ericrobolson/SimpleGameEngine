#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

#include <BaseComponent.h>

class MovementComponent : public BaseComponent
{
    public:
        MovementComponent();
        virtual ~MovementComponent();

        int GetXDelta();
        int GetYDelta();

        double SetDirectionAngleInRadians(double radians);

        double SetDirectionAngleFromCoordinates(int x1, int y1, int x2, int y2);

        double GetAngleInRadians();

        void TurnLeft(int degrees);
        void TurnRight(int degrees);

        int ForwardSpeed; // Positive number for forward movement, negative for backward movement
        int HorizontalSpeed; // Positive number for moving right, negative for moving left

    private:
        double _directionRadians;
        double GetAngleInRadians(int angle);
        const double PerpindicularRadians = 1.5708; // This is used to calculate XDelta and YDelta for horizontal movement

};

#endif // MOVEMENTCOMPONENT_H
