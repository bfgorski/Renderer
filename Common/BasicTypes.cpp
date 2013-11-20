//
//  BasicTypes.cpp
//  Renderer
//
//  Created by Benjamin Gregorski on 11/18/13.
//
//

#include "BasicTypes.h"

const Framework::vec3 VZero(0,0,0);
const Framework::vec3 VXAxis(1,0,0);
const Framework::vec3 VYAxis(0,1,0);
const Framework::vec3 VZAxis(0,0,1);

namespace Framework {
    
    Axes vec3::maxAbsComp() const {
        float f = fabs(v[XAxis]);
        Axes max = XAxis;
        
        if (fabs(v[YAxis]) > f) {
            f = fabs(v[YAxis]);
            max = YAxis;
        }
        if (fabs(v[ZAxis]) > f) {
            max = ZAxis;
        }
        
        return max;
    }
    
    Axes vec3::minAbsComp() const {
        float f = fabs(v[XAxis]);
        Axes min = XAxis;
        
        if (fabs(v[YAxis]) < f) {
            f = fabs(v[YAxis]);
            min = YAxis;
        }
        if (fabs(v[ZAxis]) < f) {
            min = ZAxis;
        }
        
        return min;
    }
}