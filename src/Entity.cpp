#include "Entity.h"
#include "BaseComponent.h"
#include <vector>
#include <memory>
Entity::Entity()
{
    _id = _nextId;
    _nextId++;
    _components.clear();
}

Entity::~Entity()
{
    //dtor
}

int Entity::_nextId = 1;

int Entity::GetId(){
    return _id;
}

void Entity::DeleteComponent(int index){
    _components.erase(_components.begin() + index);
}

bool Entity::IsEmpty(){
    return _components.empty();
}


