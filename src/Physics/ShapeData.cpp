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
    Aabb aabb;

    //todo: calculate the AABB based on the shape

    return aabb;

}
