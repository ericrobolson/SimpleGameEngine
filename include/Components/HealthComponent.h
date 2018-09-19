#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

#include "BaseComponent.h"


class HealthComponent : public BaseComponent
{
    public:
        HealthComponent();
        virtual ~HealthComponent();
        int Health;
        int MaxHealth;

    protected:

    private:
};

#endif // HEALTHCOMPONENT_H
