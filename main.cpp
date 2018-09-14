// Copyright (c) 2018, Eric Olson

#include "Entity.h"
#include "PositionComponent.h"
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

    std::shared_ptr<PositionComponent> posCom2 = std::make_shared<PositionComponent>();

    posCom2.get()->PositionX = 1;

    entity.AddComponent(posCom2);

    entity.RemoveComponent(posCom2);


    std::shared_ptr<PositionComponent> testGet;
    entity.GetComponent(testGet);

    cout << "testing:" << endl;

    if (testGet == nullptr){
        cout << "womp womp" << endl;
    }
    else{
        cout << testGet.get()->PositionX << endl;
    }

    cout << "entityId: " << entity.GetId() << endl;;

    Entity entity2;
    cout << "entity2Id: " << entity2.GetId() << endl;;


    cout << "/testing:" << endl;

    return 0;
}
