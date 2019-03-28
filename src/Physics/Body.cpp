#include "Body.h"
using namespace SGE_Physics;
Body::Body()
{
    GravityScale = 1.0_fp;
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
