#include <memory>
#include <vector>
#include "BaseWorld.h"

BaseWorld::BaseWorld()
{
    //ctor
}

BaseWorld::~BaseWorld()
{
    //dtor
}

void BaseWorld::AddEntity(std::shared_ptr<Entity> entity){
    _entities.push_back(entity);

};

void BaseWorld::RemoveEntity(int entityId){
    if (_entities.empty()){
        return;
    }

    int indexToRemove = 0;

    std::shared_ptr<Entity> entityToDelete = nullptr;

    for (int i = 0; i < _entities.size(); i++){
        indexToRemove = i;

        entityToDelete = _entities[i];

        if (entityToDelete.get()->GetId() == entityId){
            break;
        }
    }

    _entities.erase(_entities.begin() + indexToRemove);
    entityToDelete.reset();
};


void BaseWorld::Process(){
    // This is where systems are processed


    // Ideal system order:

        // InputSystem
        // CollisionSystem?
        // MovementSystem
        // DrawSystem

}
