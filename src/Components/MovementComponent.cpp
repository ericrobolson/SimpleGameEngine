#include "Components/MovementComponent.h"

MovementComponent::MovementComponent() : BaseComponent()
{
    Direction = MovementComponent::NOTMOVING;
    Speed = 0;
}

MovementComponent::~MovementComponent()
{
    //dtor
}
