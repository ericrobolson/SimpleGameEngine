// Copyright (c) 2018, Eric Olson

#include "Entity.h"
#include "Components/PositionComponent.h"
#include "Components/MovementComponent.h"
#include <iostream>
#include <memory>
#include <typeinfo>
#include <vector>


using namespace std;


int main( int argc, char* args[] )
{
    Entity entity;

    std::shared_ptr<PositionComponent> posCom = std::make_shared<PositionComponent>();

    posCom.get()->PositionX = 3;

    entity.AddComponent(posCom);

    std::shared_ptr<MovementComponent> posCom2 = std::make_shared<MovementComponent>();

    posCom2.get()->Direction = MovementComponent::LEFT;
    cout << "enum: " << MovementComponent::LEFT << endl;

    entity.AddComponent(posCom2);

    std::shared_ptr<MovementComponent> testGet;
    entity.GetComponent(testGet);

    cout << "testing:" << endl;

    if (testGet == nullptr){
        cout << "womp womp" << endl;
    }
    else{
        cout << testGet.get()->Direction << endl;
        cout << testGet.get()->Speed << endl;
    }

    cout << "/testing:" << endl;

    return 0;
}
