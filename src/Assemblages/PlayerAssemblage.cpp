#include <memory>
#include "PlayerAssemblage.h"
#include "EntityComponentManager.h"
#include "PlayerComponent.h"
#include "ColorComponent.h"
#include "PositionComponent.h"
#include "RectangleComponent.h"
#include <iostream>
PlayerAssemblage::PlayerAssemblage()
{
    //ctor
}

PlayerAssemblage::~PlayerAssemblage()
{
    //dtor
}

std::shared_ptr<int> PlayerAssemblage::GeneratePlayer(ECS::EntityComponentManager &ec){
    std::shared_ptr<int> entityIdPtr = nullptr;

    entityIdPtr = ec.AddEntity();
    if (entityIdPtr != nullptr){
        int entityId = *entityIdPtr.get();

        PlayerComponent& playerComponent = ec.AddComponent<PlayerComponent>(entityId);
        ColorComponent& colorComponent = ec.AddComponent<ColorComponent>(entityId);
        colorComponent.Red = 50;
        colorComponent.Green = 205;
        colorComponent.Blue = 50;

        PositionComponent& positionComponent = ec.AddComponent<PositionComponent>(entityId);
        positionComponent.PositionX = 300;
        positionComponent.PositionY = 300;


        RectangleComponent& rectComponent = ec.AddComponent<RectangleComponent>(entityId);
        rectComponent.Height = 15;
        rectComponent.Width = 15;
    }

    return entityIdPtr;
};
