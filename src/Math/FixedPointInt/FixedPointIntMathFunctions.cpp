#include "FixedPointInt.h"

#include <cmath>
using namespace SGE_Math;

FixedPointInt FixedPointInt::abs(){
    FixedPointInt fp;

    fp.Value = this->Value;

    if (fp.Value < 0){
        fp = -fp;
    }

    return fp;
}


FixedPointInt FixedPointInt::sqrt(){
    if (this->Value <= 0){
        return 0.0_fp;
    }

    int_fast64_t t,q,b,r;

    r = this->Value;
    b = 0x40000000;
    q = 0;

    while( b >= 256 ) {
        t = q + b;
        if( r >= t ) {
          r = r - t;
          q = t + b;
        }
        r = r * 2;     /* shift left  1 bit */
        b = b / 2;     /* shift right 1 bit */
    }
    q = q / 256;     /* shift right 8 bits */

    FixedPointInt fp;
    fp.Value = q;

    return fp;

}





FixedPointInt& FixedPointInt::maximum(FixedPointInt& a, FixedPointInt& b){
    if (a.Value >= b.Value){
        return a;
    }

    return b;
}

FixedPointInt& FixedPointInt::minimum(FixedPointInt& a, FixedPointInt& b){
    if (a.Value <= b.Value){
        return a;
    }

    return b;
}
