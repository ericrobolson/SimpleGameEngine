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

        void AddComponent(std::shared_ptr<BaseComponent> &component);
        void RemoveComponent(int index);

        std::vector<std::shared_ptr<BaseComponent>> GetComponents();

        template <class tComponent>
        tComponent GetComponent();
    protected:

    private:
        std::vector<std::shared_ptr<BaseComponent>> _components;
};

#endif // ENTITY_H
