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
    switch (mType){
    case (MaterialData::MaterialType::Rock):
        Density = 0.6_fp;
        Restitution = 0.1_fp;
        break;
    case (MaterialData::MaterialType::Wood):
        Density = 0.3_fp;
        Restitution = 0.2_fp;
        break;
    case (MaterialData::MaterialType::Metal):
        Density = 1.2_fp;
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
