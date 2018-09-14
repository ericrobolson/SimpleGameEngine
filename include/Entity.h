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
            // go thru existing components
            // if there exists a component that has a matching type, remove it and replace it with this one
            // otherwise add it
            if (!IsEmpty()){
                int numberOfComponents = _components.size();

                for (int i = 0; i < numberOfComponents; i++){
                    BaseComponent* baseComponent = _components[i].get();

                    tComponent* castedComponent = dynamic_cast<tComponent*>(baseComponent);

                    if (castedComponent != nullptr){
                        DeleteComponent(i);
                        break;
                    }
                }
            }

            _components.push_back(componentPtr);
        };

        template <class tComponent>
        void RemoveComponent(tComponent component){
            if (_components.empty()){
                return;
            }

            int numberOfComponents = _components.size();

            for (int i = 0; i < numberOfComponents; i++){
                BaseComponent* baseComponent = _components[i].get();

                tComponent* castedComponent = dynamic_cast<tComponent*>(baseComponent);

                if (castedComponent != nullptr){
                    DeleteComponent(i);
                break;
                }
            }
        };

        template <class tComponent>
        void GetComponent(tComponent*& component){
            component = nullptr;

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
