#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "FixedPointInt.h"

namespace SGE_Physics{
class Constants
{
    public:
        /// Get the scaled gravity
        static FixedPointInt GetGravity(){
            return 4.0_fp;
        }

        /// The ratio of how many units are in a meter
        static FixedPointInt GetMeterRatio(){
            // ratio of 10 units = 1 meter

            return 10.0_fp;
        }
};



}
#endif // CONSTANTS_H
