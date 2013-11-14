//
//  MathUtils.h
//  Renderer
//
//  Created by Benjamin Gregorski on 10/24/13.
//
//

#ifndef __Renderer__MathUtils__
#define __Renderer__MathUtils__

namespace Framework { namespace Math {
    
/**
 * Return a*(1-t) * b*t
 */
float lerp(const float a, const float b, const float t);

float clamp(const float value, const float min, const float max);

/**
 * Return a value in [0,255] clamping v at min/max
 */
char toByte(const float v, const float min, const float max);

float min(const float a, const float b);
float max(const float a, const float b);

}
}

#endif /* defined(__Renderer__MathUtils__) */
