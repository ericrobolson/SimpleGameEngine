// Copyright (c) 2018, Eric Olson

#include "Entity.h"
#include "PositionComponent.h"
#include <iostream>
#include <memory>

using namespace std;



int main( int argc, char* args[] )
{
    Entity entity;

    std::shared_ptr<BaseComponent> position = std::make_shared<PositionComponent>();

    ((PositionComponent*)position.get())->PositionX = 4;

    dynamic_cast<PositionComponent*>(position.get())->PositionY = 4;

    //std::shared_ptr<BaseComponent> stuff(&position);

    entity.AddComponent(position);


    cout << position.get()->GetType();


//    cout << std::dynamic_pointer_cast<PositionComponent*>(entity.GetComponents()[0].get())->PositionY;

    return 0;
}
