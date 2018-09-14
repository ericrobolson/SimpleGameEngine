// Copyright (c) 2018, Eric Olson

#include "Entity.h"
#include "PositionComponent.h"
#include <iostream>
#include <memory>
#include <typeinfo>

using namespace std;



int main( int argc, char* args[] )
{
    Entity entity;



    PositionComponent* testGet;
    entity.GetComponent(testGet);

    cout << "testing:" << endl;

    if (testGet == nullptr){
        cout << "womp womp" << endl;
    }

    cout << nullptr << endl;
    cout << testGet << endl;
    cout << "/testing:" << endl;

    return 0;
}
