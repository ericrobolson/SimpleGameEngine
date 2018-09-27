#include "PlayerAssemblage.h"
#include "EntityComponentManager.h"
#include "PlayerComponent.h"
#include "ColorComponent.h"
#include "PositionComponent.h"
#include "RectangleComponent.h"

PlayerAssemblage::PlayerAssemblage()
{
    //ctor
}

PlayerAssemblage::~PlayerAssemblage()
{
    //dtor
}

int PlayerAssemblage::GeneratePlayer(EntityComponentManager &ec){
    int entityId = -1;

    entityId = ec.AddEntity();

    if (EntityComponentManager::IsValidId(entityId)){
        PlayerComponent playerComponent = ec.AddComponent<PlayerComponent>(entityId);

        ColorComponent colorComponent = ec.AddComponent<ColorComponent>(entityId);

        PositionComponent positionComponent = ec.AddComponent<PositionComponent>(entityId);
        positionComponent.PositionX = 300;
        positionComponent.PositionY = 300;


        RectangleComponent rectComponent = ec.AddComponent<RectangleComponent>(entityId);
        rectComponent.Height = 15;
        rectComponent.Width = 15;


    }

    return entityId;
};
