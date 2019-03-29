#include "EVector.h"
using namespace SGE_Math;

EVector EVector::operator -(){
    EVector ev = *this;

    ev.X = -ev.X;
    ev.Y = -ev.Y;

    return ev;
}

EVector EVector::operator -(const EVector& rhs){
    EVector ev = *this;

    ev.X = ev.X - rhs.X;
    ev.Y = ev.Y - rhs.Y;

    return ev;
}

EVector EVector::operator +(const EVector& rhs){
    EVector ev = *this;

    ev.X = ev.X + rhs.X;
    ev.Y = ev.Y + rhs.Y;

    return ev;
}


EVector EVector::operator /(const EVector& rhs){
    //todo: test
    EVector ev = *this;

    //todo: what if zero is passed in?

    ev.X = ev.X / rhs.X;
    ev.Y = ev.Y / rhs.Y;

    return ev;
}

EVector EVector::operator /(const FixedPointInt& rhs){
    //todo: test
    EVector ev = *this;

    //todo: what if zero is passed in?

    ev.X = ev.X / rhs;
    ev.Y = ev.Y / rhs;

    return ev;
}

EVector EVector::operator *(const FixedPointInt& rhs){
    EVector ev = *this;

    ev.X = ev.X * rhs;
    ev.Y = ev.Y * rhs;

    return ev;
}
