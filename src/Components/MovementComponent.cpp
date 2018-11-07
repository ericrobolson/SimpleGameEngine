#include "Components/MovementComponent.h"
#include <math.h>

MovementComponent::MovementComponent() : BaseComponent()
{
    VerticalSpeed = 0;
    HorizontalSpeed = 0;
}

MovementComponent::~MovementComponent()
{
    //dtor
}
