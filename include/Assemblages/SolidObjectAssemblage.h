#ifndef SOLIDOBJECTASSEMBLAGE_H
#define SOLIDOBJECTASSEMBLAGE_H
#include "EntityComponentManager.h"


class SolidObjectAssemblage
{
    public:
        SolidObjectAssemblage();
        virtual ~SolidObjectAssemblage();

        static std::shared_ptr<int> Build(ECS::EntityComponentManager &ecs, int x, int y, int h, int w);
};

#endif // SOLIDOBJECTASSEMBLAGE_H
