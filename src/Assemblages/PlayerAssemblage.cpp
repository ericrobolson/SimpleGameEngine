#include "PlayerAssemblage.h"
#include <memory>

#include "EntityComponentManager.h"

#include "PlayerComponent.h"

#include "PhysicsBodyComponent.h"
#include "Aabb.h"
PlayerAssemblage::PlayerAssemblage()
{
    //ctor
}

PlayerAssemblage::~PlayerAssemblage()
{
    //dtor
}


std::shared_ptr<int> PlayerAssemblage::BuildPlayer(ECS::EntityComponentManager &ecs, SGE_Math::FixedPointInt x, SGE_Math::FixedPointInt y){
    std::shared_ptr<int> entityId = ecs.AddEntity();

    if (entityId != nullptr){
        int id = *entityId.get();

        PlayerComponent& playerComponent = ecs.AddComponent<PlayerComponent>(id);


        PhysicsBodyComponent& body = ecs.AddComponent<PhysicsBodyComponent>(id);

        SGE_Physics::Aabb aabb;
        aabb.HalfHeight = 25.0_fp;
        aabb.HalfWidth = 25.0_fp;

        EVector position;
        position.X = 450.0_fp;
        position.Y = 40.0_fp;

        body.Body.IsStaticObject = false;

        body.Body.Initialize(SGE_Physics::MaterialData::MaterialType::Wood, position, aabb);
    }

    return entityId;
}
