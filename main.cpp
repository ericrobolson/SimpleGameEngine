// Copyright (c) 2018, Eric Olson

#include "Entity.h"
#include "Components/PositionComponent.h"
#include "Components/MovementComponent.h"
#include "Worlds/GameWorld.h"

#include <iostream>
#include <memory>
#include <typeinfo>
#include <vector>
#include <SDL.h>



using namespace std;


int main( int argc, char* args[] )
{
/*
    Entity entity;

    std::shared_ptr<PositionComponent> posCom = std::make_shared<PositionComponent>();

    posCom.get()->PositionX = 3;

    entity.AddComponent(posCom);

    std::shared_ptr<MovementComponent> posCom2 = std::make_shared<MovementComponent>();

    entity.AddComponent(posCom2);

    std::shared_ptr<MovementComponent> testGet;
    entity.GetComponent(testGet);

    cout << "testing:" << endl;
*/

    GameWorld gameWorld;

    while(gameWorld.Process()){}

    return 0;
}
