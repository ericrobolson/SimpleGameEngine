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
    // Check out https://www.engineeringtoolbox.com/wood-density-d_40.html
    // and https://www.engineeringtoolbox.com/density-solids-d_1265.html
    // for densities

    // Densest object is .99, which is steel which is 488 lb/ft^3
    FixedPointInt steelPhysicsDensity = 0.9_fp;
    FixedPointInt steelActualDensity = 488.0_fp;

    FixedPointInt oakActualDensity = 50.0_fp; // 50 lb/ft^3
    FixedPointInt oakPhysicsDensity = steelPhysicsDensity * (oakActualDensity / steelActualDensity);

    FixedPointInt rockActualDensity = 125.0_fp; // dense concrete, 125-150 lb/ft^3
    FixedPointInt rockPhysicalDensity = steelPhysicsDensity * (rockActualDensity / steelActualDensity);



    switch (mType){
    case (MaterialData::MaterialType::Rock):
        Density = rockPhysicalDensity;
        Restitution = 0.1_fp;
        Friction = 0.8_fp;

        break;
    case (MaterialData::MaterialType::Wood):
        Density = oakActualDensity;
        Restitution = 0.1_fp;
        Friction = 0.5_fp;
        break;
    case (MaterialData::MaterialType::Metal):
        Density = steelPhysicsDensity;
        Restitution = 0.05_fp;
        Friction = 0.7_fp;
        break;
    case (MaterialData::MaterialType::BouncyBall):
        Density = 0.3_fp;
        Restitution = 0.8_fp;
        Friction = 0.5_fp;
        break;
    case (MaterialData::MaterialType::SuperBall):
        Density = 0.3_fp;
        Restitution = 0.95_fp;
        Friction = 0.5_fp;
        break;
    case (MaterialData::MaterialType::Pillow):
        Density = 0.1_fp;
        Restitution = 0.2_fp;
        Friction = 0.5_fp;
        break;
    case (MaterialData::MaterialType::StaticObject):
        Density = 0.0_fp;
        Restitution = 0.4_fp;
        Friction = 0.4_fp;
        break;

    }


}
