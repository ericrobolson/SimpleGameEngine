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
        FixedPointInt inverseMass;

        // set the inverseMass
        if (Mass != 0.0_fp){
            inverseMass = 1.0_fp / Mass;
        }

        _inverseMass = std::make_shared<FixedPointInt>(inverseMass);
    }

    return *_inverseMass;
}
