#include "Entity.h"
#include "BaseComponent.h"
#include <vector>
#include <memory>

Entity::Entity()
{
    _id = _nextId;
    _nextId++;
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

    std::shared_ptr<BaseComponent> componentToErase = _components.at(index);

    _components.erase(_components.begin() + index);

    componentToErase.reset();
}

bool Entity::IsEmpty(){
    return _components.empty();
}


