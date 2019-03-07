#include "Body.h"
using namespace SGE_Physics;
Body::Body()
{
    //ctor
}

Body::~Body()
{
    //dtor
}

Aabb Body::GetRoughAabb(){
    Aabb a = Shape.GetAabb();

    a.Position = Transform.Position;

    return a;


}
