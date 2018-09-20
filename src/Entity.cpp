#include "Entity.h"
#include "BaseComponent.h"
#include <vector>
#include <memory>
#include <string>
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
    printf("TESTING COMPONENTS: \n");

    if (_components.empty()){
        printf("isnull");
    }
    printf("notnull");
    return _components.empty();
}


