#include "StaticSpriteComponent.h"
#include <math.h>


StaticSpriteComponent::StaticSpriteComponent() : BaseComponent()
{
    _rotation = 0;
    ZIndex = 100;
    //ctor
}

StaticSpriteComponent::~StaticSpriteComponent()
{
    //dtor
}



double StaticSpriteComponent::GetRotation(){
    return _rotation;
}

double StaticSpriteComponent::SetRotation(double angle){
    angle = fmod(angle, 360);
    if (angle < 0){
        angle += 360;
    }

    return angle;
}
