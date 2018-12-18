#include "NetworkSystem.h"
#include "ThreadPool.h"
#include "ThreadPool.h"
#include "SingleplayerNetwork.h"

NetworkSystem::NetworkSystem()
{
    //ctor
    //_network = SingleplayerNetwork();
}

NetworkSystem::~NetworkSystem()
{
    //dtor
}

bool NetworkSystem::Process(ECS::EntityComponentManager &ecs){
    // send
    // recieve
    return true;
}
