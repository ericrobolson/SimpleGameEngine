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
        aabb.HalfHeight = 16.0_fp;
        aabb.HalfWidth = 16.0_fp;
        body.Body.Mass.Mass = 1.25_fp;
        body.Body.Material.Density = 1.0_fp;
        body.Body.Material.Restitution = 0.4_fp;
        body.Body.Shape.SetAabb(aabb);
        body.Body.Transform.Position.X = x;
        body.Body.Transform.Position.Y = y;
        body.Body.GravityScale = 1.0_fp;
    }

    return entityId;
}
