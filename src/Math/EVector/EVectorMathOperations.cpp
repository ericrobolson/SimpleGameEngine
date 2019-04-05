#include "EVector.h"
using namespace SGE_Math;

FixedPointInt EVector::dot(const EVector& rhs){
    FixedPointInt fp;

    fp = this->X * rhs.X + this->Y * rhs.Y;

    return fp;
}

void EVector::Reset(){
    this->X = 0.0_fp;
    this->Y = 0.0_fp;
}

FixedPointInt EVector::magnitude(){
    //todo: test
    FixedPointInt fp;
    fp = (X * X + Y * Y).sqrt();
    return fp;
}

// sqrt 6.1 = 2.46981780705
// 601 - 24.5153013443


void EVector::Normalize(){
    //todo: test

    FixedPointInt magnitude;
    magnitude = this->magnitude();

    X = X / magnitude;
    Y = Y / magnitude;
}

EVector::Projection EVector::project(std::vector<EVector> points){
    // Note: The axis (or 'this') must be normalized for it to calculate properly

    Projection p;

    int i = 0;

    p.Min = this->dot(points[i]);
    p.Max = p.Min;

    for (i = 1; i < points.size(); i++){
        FixedPointInt proj = this->dot(points[i]);

        if (proj < p.Min){
            p.Min = proj;
        }else if (proj > p.Max){
            p.Max = proj;
        }
    }

    return p;
}
