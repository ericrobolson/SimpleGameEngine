#include "BaseComponent.h"

int BaseComponent::nextGlobalId = 1;

int BaseComponent::GetId() const{
    return _id;
}

int BaseComponent::GetType(){
    return 0;
}

BaseComponent::BaseComponent()
{
    // Set the Id and increment the global id. This allows uniqueness checks for components.
    _id = nextGlobalId;
    nextGlobalId +=1;
}

BaseComponent::~BaseComponent()
{
    //todo: cleanup
    //dtor
}

bool BaseComponent::operator==(const BaseComponent &c1){
    if (GetId() == c1.GetId()){
        return true;
    }

    return false;
};
