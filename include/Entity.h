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
        bool IsEmpty();

        template <class tComponent>
        void AddComponent(std::shared_ptr<tComponent> &componentPtr){
            if (!IsEmpty()){
                // Remove any components that have the same type so that only one component of a type can be added
                RemoveComponent(componentPtr);
            }
            _components.push_back(componentPtr);
        };

        template <class tComponent>
        void RemoveComponent(std::shared_ptr<tComponent> component){
            if (_components.empty()){
                return;
            }

            int numberOfComponents = _components.size();

            for (int i = 0; i < numberOfComponents; i++){
                std::shared_ptr<BaseComponent> baseComponent = _components[i];

                std::shared_ptr<tComponent> castedComponent = std::dynamic_pointer_cast<tComponent>(baseComponent);

                if (castedComponent != nullptr){
                    DeleteComponent(i);
                break;
                }
            }
        };

        template <class tComponent>
        void GetComponent(std::shared_ptr<tComponent>& component){
            component.reset();

            int numberOfComponents = _components.size();
            for (int i = 0; i < numberOfComponents; i++){
                // iterate over components, then return the first element of the type of tEntity
                std::shared_ptr<BaseComponent> baseComponent = _components[i];

                std::shared_ptr<tComponent> castedComponent = std::dynamic_pointer_cast<tComponent>(baseComponent);

                if (castedComponent != nullptr){
                    component = castedComponent;
                }
            }
        };

        int GetId();

    private:
        int _id;
        static int _nextId;

        void DeleteComponent(int index);

        std::vector<std::shared_ptr<BaseComponent>> _components;
};

#endif // ENTITY_H
