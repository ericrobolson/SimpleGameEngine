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
/*
template <class tComponent>
void Entity::AddComponent(std::shared_ptr<BaseComponent> &componentPtr){
    // go thru existing components
    // if there exists a component that has a matching type, remove it and replace it with this one
    // otherwise add it

    if (!IsEmpty()){
        int numberOfComponents = _components.size();

        for (int i = 0; i < numberOfComponents; i++){
            BaseComponent baseComponent = _components[i].get();

            tComponent castedComponent = dynamic_cast<tComponent>(baseComponent);

            if (castedComponent != nullptr){
                DeleteComponent(i);
                break;
            }
        }
    }

    _components.push_back(componentPtr);
}

template <class tComponent>
void Entity<tComponent>::RemoveComponent(){
    if (_components.empty()){
        return;
    }

    int numberOfComponents = _components.size();

    for (int i = 0; i < numberOfComponents; i++){
        BaseComponent baseComponent = _components[i].get();

        tComponent castedComponent = dynamic_cast<tComponent>(baseComponent);

        if (castedComponent != nullptr){
            DeleteComponent(i);
            break;
        }
    }

}

template <class tComponent>
void Entity<tComponent>::DeleteComponent(int index){

    std::shared_ptr<BaseComponent> componentToErase = _components.at(index);

    _components.erase(_components.begin() + index);

    componentToErase.reset();
}

template <class tComponent>
bool Entity<tComponent>::IsEmpty(){
return _components.empty();
}

*/


