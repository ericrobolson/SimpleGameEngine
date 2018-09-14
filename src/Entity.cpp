#include "Entity.h"
#include "BaseComponent.h"
#include <vector>
#include <memory>

Entity::Entity()
{
    //ctor
}

Entity::~Entity()
{
    //dtor
}

void Entity::DeleteComponent(int index){

    std::shared_ptr<BaseComponent> componentToErase = _components.at(index);

    _components.erase(_components.begin() + index);

    componentToErase.reset();
}

bool Entity::IsEmpty(){
    return _components.empty();
}


