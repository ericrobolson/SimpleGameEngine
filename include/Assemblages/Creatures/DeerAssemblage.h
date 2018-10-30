#ifndef DEERASSEMBLAGE_H
#define DEERASSEMBLAGE_H
#include "EntityComponentManager.h"


class DeerAssemblage
{
    public:
        DeerAssemblage();
        virtual ~DeerAssemblage();

        static std::shared_ptr<int> BuildDeer(ECS::EntityComponentManager &ecs);
    protected:

    private:
};

#endif // DEERASSEMBLAGE_H
