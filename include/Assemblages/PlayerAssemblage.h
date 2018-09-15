#ifndef PLAYERASSEMBLAGE_H
#define PLAYERASSEMBLAGE_H

#include <memory>
#include "Entity.h"

namespace PlayerAssemblage{
    std::shared_ptr<Entity> CreatePlayerEntity();
}

#endif // PLAYERASSEMBLAGE_H
