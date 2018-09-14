#ifndef ENTITY_H
#define ENTITY_H
#include <vector>
#include <memory>
#include "BaseComponent.h"
class Entity
{
    public:
        Entity();
        virtual ~Entity();
/*
        template <class tComponent>
        void AddComponent(std::shared_ptr<BaseComponent> &componentPtr);

        template <class tComponent>
        void RemoveComponent();

        bool IsEmpty();
*/
        template <class tComponent>
        void GetComponent(tComponent* component){
            component = nullptr;
            // note: need to determine if this is actually working.
            int numberOfComponents = _components.size();
            for (int i = 0; i < numberOfComponents; i++){
                // iterate over components, then return the first element of the type of tEntity
                BaseComponent* baseComponent = _components[i].get();

                tComponent* castedComponent = dynamic_cast<tComponent*>(baseComponent);

                if (castedComponent != nullptr){
                    component = castedComponent;
                }
            }

        };

    protected:

    private:
        void DeleteComponent(int index);

        std::vector<std::shared_ptr<BaseComponent>> _components;
};

#endif // ENTITY_H
