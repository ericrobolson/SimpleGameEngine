#include "EntityComponentManager.h"

EntityComponentManager::EntityComponentManager()
{
    //ctor
}

EntityComponentManager::~EntityComponentManager()
{
    // mark all entities as inactive, so that they are marked for cleanup

    for (int i = 0; i < takenEntityIds.count(); i++){

        int entityToMarkAsInactive = takenEntityIds[i];

        MarkEntityInactive(entityToMarkAsInactive);
    }

    DeleteInactiveEntites();

    // delete other misc memory shit

    //dtor
}
