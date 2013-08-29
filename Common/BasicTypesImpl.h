//
//  BasicTypeImpl.h
//  Renderer
//
//  Created by Benjamin Gregorski on 11/18/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef Renderer_BasicTypeImpl_h
#define Renderer_BasicTypeImpl_h

#include "BasicTypes.h"

namespace Framework { namespace Math {
 
float min(const float a, const float b);
float max(const float a, const float b);
    
float vec3Len(const vec3& v);
float vec3Len(const vec4& v);
float vec4Len(const vec4& v);

void vec3Normalize(vec3& v);
void vec4Normalize3(vec4& v);

float vec3Dist(const vec3& a, const vec3& b);
    
/**
 * Return the distance squared for fast comparisons.
 */
float vec3FastDist(const vec3& a, const vec3& b);
    
vec3 vec3Scale(const vec3& a, const float f);
vec3 vec3Scale(const float f, const vec3& a);
vec3 vec3AMinusB(const vec3& a, const vec3& b);
vec3 vec3APlusB(const vec3& a, const vec3& b);

/*
 * Return component wise A*X + B
 */
vec3 vec3AXPlusB(const vec3& a, const float x, const vec3& b);
    
/*
 * Return component wise A*X + B*Y.
 */
vec3 vec3AXPlusBY(const vec3& a, const float x, const vec3&b, const float y);
    
float dot3(const vec3& a, const vec3& b);
float dot3(const vec4& a, const vec4& b);
float dot4(const vec4& a, const vec4& b);

vec3 cross(const vec3& a, const vec3& b);
    
/*
 * Affine Combination that interpolates a to b so t = [0,1] => [a,b]
 */
vec3 affine3(const vec3& a, const vec3&b, const float t);
    
}
}
#endif
