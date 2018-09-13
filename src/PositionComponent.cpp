#include "PositionComponent.h"

PositionComponent::PositionComponent() : BaseComponent()
{
    //ctor
}

int PositionComponent::GetType(){
    return 1;
}

PositionComponent::~PositionComponent()
{
    //dtor
}
