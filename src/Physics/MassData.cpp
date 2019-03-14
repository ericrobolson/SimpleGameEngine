#include "MassData.h"
using namespace SGE_Physics;
MassData::MassData()
{
    //ctor
}

MassData::~MassData()
{
    //dtor
}


FixedPointInt MassData::InverseMass(){
    //todo: test
    if (_inverseMass == nullptr){
        _inverseMass = std::make_shared<FixedPointInt>();

        // set the inverseMass
        if (Mass != 0.0_fp){
            *_inverseMass = 1.0_fp / Mass;
        }
    }

    return *_inverseMass;
}
