#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include "EntityComponentManager.h"
#include <string>

class LevelLoader
{
    public:
        LevelLoader();
        virtual ~LevelLoader();

        void LoadLevel(std::string levelName, ECS::EntityComponentManager &ecs);
};

#endif // LEVELLOADER_H
