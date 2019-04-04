#include "CollisionData.h"
using namespace SGE_Physics;
CollisionData::CollisionData(Body& entity1, Body& entity2) : Entity1(entity1), Entity2(entity2)
{
    //ctor
}

CollisionData::~CollisionData()
{
    //dtor
}
