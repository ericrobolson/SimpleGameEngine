#ifndef ENTITY_H
#define ENTITY_H
#include <list>
#include "BaseComponent.h"

class Entity
{
    public:
        Entity();
        virtual ~Entity();

        void AddComponent(BaseComponent &component);
        void RemoveComponent(BaseComponent &component);
    protected:

    private:
        std::list<BaseComponent> _components;
};

#endif // ENTITY_H
