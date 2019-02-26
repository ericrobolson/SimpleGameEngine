#include "EVector.h"

using namespace SGE_Math;

EVector::EVector()
{
    //ctor
}

EVector::EVector(const EVector& e)
{
    *this = e;
}

EVector::~EVector()
{
    //dtor
}

EVector& EVector::operator -(const EVector& rhs){
    return *this;
}
EVector& EVector::operator *(const EVector& rhs){
    return *this;
}
EVector& EVector::operator +(const EVector& rhs){
    return *this;
}
EVector& EVector::operator /(const EVector& rhs){
    return *this;
}


