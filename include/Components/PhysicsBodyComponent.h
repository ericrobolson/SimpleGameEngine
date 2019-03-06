#ifndef PHYSICSBODYCOMPONENT_H
#define PHYSICSBODYCOMPONENT_H

#include "BaseComponent.h"

#include "Body.h"

class PhysicsBodyComponent : public BaseComponent
{
    public:
        PhysicsBodyComponent();
        virtual ~PhysicsBodyComponent();

        SGE_Physics::Body Body;

    protected:

    private:
};

#endif // PHYSICSBODYCOMPONENT_H
