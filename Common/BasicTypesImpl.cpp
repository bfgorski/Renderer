//
//  BasicTypes.cpp
//  Renderer
//
//  Created by Benjamin Gregorski on 11/18/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "BasicTypesImpl.h"

namespace Framework { namespace Math {
    
float min(const float a, const float b) {
    return ((a > b) ? b : a);
}

float max(const float a, const float b) {
    return ((a > b) ? a : b);
}
    
float vec3Len(const vec3& v) {
     return sqrt(dot3(v, v));
}

float vec3Len(const vec4& v) {
    return sqrt(dot3(v ,v));
}

float vec4Len(const vec4& v) {
    return sqrt(dot4(v ,v));
}

void vec3Normalize(vec3& v) {
    float len = Math::vec3Len(v);
    len = 1.0f/len;
    v.v[X] *= len;
    v.v[Y] *= len;
    v.v[Z] *= len;
}

void vec4Normalize3(vec4& v)
{
    float len = Math::vec3Len(v);
    len = 1.0f/len;
    v.v[X] *= len;
    v.v[Y] *= len;
    v.v[Z] *= len;
}
    
float vec3Dist(const vec3& a, const vec3& b) {
    float x = a.v[0] - b.v[0];
    float y = a.v[1] - b.v[1];
    float z = a.v[2] - b.v[2];
    return sqrt(x*x + y*y + z*z);
}

float vec3FastDist(const vec3& a, const vec3& b) {
    float x = a.v[0] - b.v[0];
    float y = a.v[1] - b.v[1];
    float z = a.v[2] - b.v[2];
    return (x*x + y*y + z*z);
}
    
vec3 vec3Scale(const vec3& a, const float f) {
    return vec3(a.v[0]*f, a.v[1]*f, a.v[2]*f);
}
    
vec3 vec3Scale(const float f, const vec3& a) {
    return vec3(a.v[0]*f, a.v[1]*f, a.v[2]*f);
}

vec3 vec3AMinusB(const vec3& a, const vec3& b) {
    vec3 v(0,0,0);
    v.v[0] = a.v[0] - b.v[0];
    v.v[1] = a.v[1] - b.v[1];
    v.v[2] = a.v[2] - b.v[2];
    return v;
}
    
vec3 vec3APlusB(const vec3& a, const vec3& b) {
    vec3 v(0,0,0);
    v.v[0] = a.v[0] + b.v[0];
    v.v[1] = a.v[1] + b.v[1];
    v.v[2] = a.v[2] + b.v[2];
    return v;
}

vec3 vec3AXPlusB(const vec3& a, const float x, const vec3& b) {
    return (vec3(a.v[0]*x + b.v[0], a.v[1]*x + b.v[1], a.v[2]*x + b.v[2]));
}
   
vec3 vec3AXPlusBY(const vec3& a, const float x, const vec3&b, const float y) {
    return (vec3(a.v[0]*x + b.v[0]*y, a.v[1]*x + b.v[1]*y, a.v[2]*x + b.v[2]*y));
}
    
float dot3(const vec3& a, const vec3& b) {
    return (a.v[0]*b.v[0] + a.v[1]*b.v[1] + a.v[2]*b.v[2]);
}

float dot3(const vec4& a, const vec4& b) {
    return (a.v[0]*b.v[0] + a.v[1]*b.v[1] + a.v[2]*b.v[2]);

}

float dot4(const vec4& a, const vec4& b) {
    return (a.v[0]*b.v[0] + a.v[1]*b.v[1] + a.v[2]*b.v[2] + a.v[3]*b.v[3]);
}
    
vec3 cross(const vec3& v1, const vec3& v2) {
    vec3 vv ;
    vv.v[0] = v1.v[1] * v2.v[2] - v1.v[2] * v2.v[1] ;
    vv.v[1] = - v1.v[0] * v2.v[2] + v1.v[2] * v2.v[0] ;
    vv.v[2] = v1.v[0] * v2.v[1] - v1.v[1] * v2.v[0] ;
    return vv;
}
    
vec3 affine3(const vec3& a, const vec3& b, const float t) {
    return vec3(a.v[0] + t * (b.v[0] - a.v[0]),
                a.v[1] + t * (b.v[1] - a.v[1]),
                a.v[2] + t * (b.v[2] - a.v[2]));
}
    
}

    
    
    
    
    
}
