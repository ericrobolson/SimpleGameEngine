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

std::vector<std::shared_ptr<BaseComponent>> Entity::GetComponents(){
    return _components;
}


void Entity::AddComponent(std::shared_ptr<BaseComponent> &component){
    _components.push_back(component);
}

void Entity::RemoveComponent(int index){
    if (_components.empty()){
        return;
    }

    // todo: _components.erase[index];
}


template <class tComponent>
tComponent Entity::GetComponent(){

    int num = _components.size();
    for (int i = 0; i < num; i++){
        // iterate over components, then return the first element of the type of tEntity
    }


    return nullptr;
}
