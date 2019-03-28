#include "MaterialData.h"

using namespace SGE_Physics;
MaterialData::MaterialData()
{
    //ctor
}

MaterialData::~MaterialData()
{
    //dtor
}

void MaterialData::SetMaterialType(MaterialType mType){
    // Densest object is .99, which is steel which is 488 lb/ft^3
    FixedPointInt steelPhysicsDensity = 0.6_fp;
    FixedPointInt steelActualDensity = 488.0_fp;

    FixedPointInt oakActualDensity = 50.0_fp;


    switch (mType){
    case (MaterialData::MaterialType::Rock):
        Density = 0.6_fp;
        Restitution = 0.1_fp;
        break;
    case (MaterialData::MaterialType::Wood):
        Density = steelPhysicsDensity * (oakActualDensity / steelActualDensity);
        Restitution = 0.2_fp;
        break;
    case (MaterialData::MaterialType::Metal):
        Density = steelPhysicsDensity;
        Restitution = 0.05_fp;
        break;
    case (MaterialData::MaterialType::BouncyBall):
        Density = 0.3_fp;
        Restitution = 0.8_fp;
        break;
    case (MaterialData::MaterialType::SuperBall):
        Density = 0.3_fp;
        Restitution = 0.95_fp;
        break;
    case (MaterialData::MaterialType::Pillow):
        Density = 0.1_fp;
        Restitution = 0.2_fp;
        break;
    case (MaterialData::MaterialType::StaticObject):
        Density = 0.0_fp;
        Restitution = 0.4_fp;
        break;

    }


}
