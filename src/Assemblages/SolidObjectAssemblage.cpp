#include "SolidObjectAssemblage.h"
#include <memory>
#include "EntityComponentManager.h"
#include "HitboxComponent.h"
#include "PositionComponent.h"
#include "ImpassibleComponent.h"

SolidObjectAssemblage::SolidObjectAssemblage()
{
    //ctor
}

SolidObjectAssemblage::~SolidObjectAssemblage()
{
    //dtor
}


std::shared_ptr<int> SolidObjectAssemblage::Build(ECS::EntityComponentManager &ecs, int x, int y, int h, int w){
    std::shared_ptr<int> entityId = ecs.AddEntity();

    if (entityId != nullptr){
        int id = *entityId.get();

        HitboxComponent& hitBox = ecs.AddComponent<HitboxComponent>(id);
        hitBox.SetHeight(h);
        hitBox.SetWidth(w);

        PositionComponent& positionComponent = ecs.AddComponent<PositionComponent>(id);
        positionComponent.PositionX = x;
        positionComponent.PositionY = y;

        ecs.AddComponent<ImpassibleComponent>(id);
    }

    return entityId;
}
