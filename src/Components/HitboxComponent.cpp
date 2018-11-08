#include "HitboxComponent.h"


const int EvenMultiplier = 2;

HitboxComponent::HitboxComponent()
{
    SetHeight(8);
    SetWidth(8);
}

HitboxComponent::~HitboxComponent()
{
    //dtor
}


int HitboxComponent::SetHeight(int height){
    if (height <1){
        height = 1;
    }

    _height = EvenMultiplier * height;
};

int HitboxComponent::SetWidth(int width){
    if (width <1){
        width = 1;
    }

    _width = EvenMultiplier * width;
}


int HitboxComponent::GetHeight(){
    return _height;
}

int HitboxComponent::GetWidth(){
    return _width;
}
