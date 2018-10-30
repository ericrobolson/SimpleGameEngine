#include "DeerAssemblage.h"
#include "EntityComponentManager.h"

#include "AiComponent.h"

#include "LivingComponent.h"
#include "HerbivoreComponent.h"
#include "OrganicComponent.h"

DeerAssemblage::DeerAssemblage()
{
    //ctor
}

DeerAssemblage::~DeerAssemblage()
{
    //dtor
}

std::shared_ptr<int> DeerAssemblage::BuildDeer(ECS::EntityComponentManager &ecs){
    std::shared_ptr<int> entity = ecs.AddEntity();

    if (entity != nullptr){
        int entityId = *entity;
        ecs.AddComponent<AiComponent>(entityId);
        ecs.AddComponent<LivingComponent>(entityId);
        ecs.AddComponent<HerbivoreComponent>(entityId);
        ecs.AddComponent<OrganicComponent>(entityId);
    }

    return entity;
}
