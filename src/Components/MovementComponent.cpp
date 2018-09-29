#include "Components/MovementComponent.h"
#include <math.h>

MovementComponent::MovementComponent() : BaseComponent()
{
    _directionRadians = 0;
    ForwardSpeed = 0;
    HorizontalSpeed = 0;
}

MovementComponent::~MovementComponent()
{
    //dtor
}

double MovementComponent::GetAngleInRadians(){
    return _directionRadians;
};

int MovementComponent::GetXDelta(){
    int xDelta = 0;

    xDelta += ForwardSpeed * cos(_directionRadians);
    xDelta += HorizontalSpeed * cos(_directionRadians + PerpindicularRadians);

    return xDelta;
}


int MovementComponent::GetYDelta(){
    int yDelta = 0;

    yDelta += ForwardSpeed * sin(_directionRadians);
    yDelta += HorizontalSpeed * sin(_directionRadians + PerpindicularRadians);

    return yDelta;
}

double MovementComponent::SetDirectionAngleInRadians(double radians){
    const double radiansInACircle = 6.28319;

    // Boundary handling for radians over 360*
    while (radians >= radiansInACircle){
        radians -= radiansInACircle;
    }

    // Boundary handling for radians under 360*
    while (radians < 0){
        radians += radiansInACircle;
    }


    _directionRadians = radians;
    return _directionRadians;
}

double MovementComponent::SetDirectionAngleFromCoordinates(int x1, int y1, int x2, int y2){

    _directionRadians = atan2(y2 - y1, x2 - x1);

    return _directionRadians;
}

double DegreesToRadians(int degrees){
    return 0.0174533 * degrees; // 0.0174533 radians in a degree
}

void MovementComponent::TurnLeft(int degrees){
    double radians = DegreesToRadians(degrees);
    SetDirectionAngleInRadians(_directionRadians - radians);
}

void MovementComponent::TurnRight(int degrees){
    double radians = DegreesToRadians(degrees);
    SetDirectionAngleInRadians(_directionRadians + radians);
}
