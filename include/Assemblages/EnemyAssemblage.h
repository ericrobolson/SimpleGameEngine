#ifndef ENEMYASSEMBLAGE_H
#define ENEMYASSEMBLAGE_H
#include <memory>
#include "EntityComponentManager.h"

class EnemyAssemblage
{
    public:
        EnemyAssemblage();
        virtual ~EnemyAssemblage();

        static std::shared_ptr<int> GenerateEnemy(ECS::EntityComponentManager &ec);


    protected:

    private:
};

#endif // ENEMYASSEMBLAGE_H
