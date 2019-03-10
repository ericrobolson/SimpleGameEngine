#include "ShapeData.h"
#include "Aabb.h"
using namespace SGE_Physics;
ShapeData::ShapeData()
{
    //ctor
}

ShapeData::~ShapeData()
{
    //dtor
}

Aabb ShapeData::GetAabb(){
    return _aabb;
}

void ShapeData::SetAabb(Aabb aabb){
    _aabb = aabb;
}
