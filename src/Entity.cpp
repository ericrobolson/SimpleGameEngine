#include "Entity.h"
#include <list>
#include "BaseComponent.h"

Entity::Entity()
{
    //ctor
}

Entity::~Entity()
{
    //dtor
}

void Entity::AddComponent(BaseComponent &component){
    _components.push_back(component);
    _components.unique();
}

void Entity::RemoveComponent(BaseComponent &component){
    if (_components.empty()){
        return;
    }

    _components.remove(component);
}
