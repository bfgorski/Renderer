//
//  MathUtils.cpp
//  Renderer
//
//  Created by Benjamin Gregorski on 10/24/13.
//
//

#include "MathUtils.h"

namespace Framework { namespace Math {
   
/**
 * Return a*(1-t) * b*t
 */
float lerp(const float a, const float b, const float t) {
    return (a + t*(b - a));
}

float clamp(const float value, const float min, const float max) {
    return ((value > max) ? max : ((value < min) ? min : value));
}

char toByte(const float v, const float min, const float max) {
    float vNew = clamp(v,min,max);
    return static_cast<char>(255.0*(vNew-min)/(max-min));
}

float min(const float a, const float b) {
    return ((a > b) ? b : a);
}

float max(const float a, const float b) {
    return ((a > b) ? a : b);
}
   
}
}