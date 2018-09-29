#include <memory>
#include "EntityComponentManager.h"
#include "EnemyAssemblage.h"
#include "EntityComponentManager.h"
#include "PlayerComponent.h"
#include "ColorComponent.h"
#include "PositionComponent.h"
#include "RectangleComponent.h"
#include "MovementComponent.h"
#include "EnemyComponent.h"

EnemyAssemblage::EnemyAssemblage()
{
    //ctor
}

EnemyAssemblage::~EnemyAssemblage()
{
    //dtor
}

std::shared_ptr<int> EnemyAssemblage::GenerateEnemy(ECS::EntityComponentManager &ec){
    std::shared_ptr<int> entityIdPtr = nullptr;

    entityIdPtr = ec.AddEntity();
    if (entityIdPtr != nullptr){
        int entityId = *entityIdPtr.get();

        EnemyComponent& enemyComponent = ec.AddComponent<EnemyComponent>(entityId);
        ColorComponent& colorComponent = ec.AddComponent<ColorComponent>(entityId);
        colorComponent.Red = 255;
        colorComponent.Green = 0;
        colorComponent.Blue = 0;

        PositionComponent& positionComponent = ec.AddComponent<PositionComponent>(entityId);
        positionComponent.PositionX = 150;
        positionComponent.PositionY = 150;

        ec.AddComponent<MovementComponent>(entityId);


        RectangleComponent& rectComponent = ec.AddComponent<RectangleComponent>(entityId);
        rectComponent.Height = 15;
        rectComponent.Width = 15;
    }

    return entityIdPtr;
};
