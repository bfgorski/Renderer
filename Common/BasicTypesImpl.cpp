//
//  BasicTypes.cpp
//  Renderer
//
//  Created by Benjamin Gregorski on 11/18/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "BasicTypesImpl.h"

const float PLANE_INTERSECTION_THRESHOLD = 1e-6;

namespace Framework { namespace Math {
    
/*
 * Combine light and surface colors.
 */
Color lightSurface(
                   const Color& lightDiffuse, const Color& surfaceDiffuse,
                   const Color& lightSpec, const Color& surfaceSpec,
                   const Color& lightAmb, const Color& surfaceAmb) {
    Color c(
            lightDiffuse.c[Red]*surfaceDiffuse.c[Red] + lightSpec.c[Red]*surfaceSpec.c[Red] + lightAmb.c[Red]*surfaceAmb.c[Red],
            lightDiffuse.c[Green]*surfaceDiffuse.c[Green] + lightSpec.c[Green]*surfaceSpec.c[Green] + lightAmb.c[Green]*surfaceAmb.c[Green],
            lightDiffuse.c[Blue]*surfaceDiffuse.c[Blue] + lightSpec.c[Blue]*surfaceSpec.c[Blue] + lightAmb.c[Blue]*surfaceAmb.c[Blue],
            surfaceDiffuse.c[Alpha]
            );
    return c;
}
    
bool isEqual(const vec3& v0, const vec3& v1, const float delta) {
    for (int i = 0; i < 3; ++i) {
        if (fabs(v0.v[i] - v1.v[i]) > delta) {
            return false;
        }
    }
    return true;
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

float vec3FastLen(const vec3& v) {
    return dot3(v,v);
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
    
void createAxes(const VectorF& uAxis, VectorF& vAxis, VectorF& wAxis) {
    // Cross uAxis with the canonical vector furthest from it
    Axes min = uAxis.minAbsComp();
    
    switch (min) {
        case XAxis:
            vAxis = Math::cross(uAxis, VXAxis);
            break;
        case YAxis:
            vAxis = Math::cross(uAxis, VYAxis);
            break;
        case ZAxis:
            vAxis = Math::cross(uAxis, VZAxis);
            break;
        default:
            break;
    }
    
    Math::vec3Normalize(vAxis);
    wAxis = Math::cross(vAxis, uAxis);
    Math::vec3Normalize(wAxis);
    
    return;
}
    
vec3 affine3(const vec3& a, const vec3& b, const float t) {
    return vec3(a.v[0] + t * (b.v[0] - a.v[0]),
                a.v[1] + t * (b.v[1] - a.v[1]),
                a.v[2] + t * (b.v[2] - a.v[2]));
}
    
    
/**
 * Intersect a Ray with a plane defined by a point and a normal
 */
bool planeIntersect(const Ray& r, const PointF& point, const VectorF& normal, PointF& intersection) {
    const PointF& rp = r.getPos();
    float dotNormalRayDir = Math::dot3(normal, r.getDir());
    
    // Is the ray perpendicular to the plane's normal?
    if (fabs(dotNormalRayDir) < PLANE_INTERSECTION_THRESHOLD) {
        return false;
    }
    
    // Determine which side of the plane the point is on
    float D = -Math::dot3(normal, point);
    float distFromPlane = Math::dot3(normal, rp) + D;
    float t = distFromPlane/dotNormalRayDir;
    
    // > 0 if ray and normal are in the same direction and
    // the ray is on the normal side of the plane or
    // If the ray and normal point in opposite directions and
    // the ray is not on the normal side of the plane
    if (t > 0) {
        return false;
    }
    
    intersection = Math::vec3AXPlusB(r.getDir(), -t, r.getPos());
    return true;
}

/**
 * Intersect a Ray with a plane defined by the 4 coefficients Ax + By + Cz + D = 0.
 * A,B,C are the plane normal
 */
bool planeIntersect(const Ray& r, const float *plane, PointF& intersection) {
    Normal normal(plane[0], plane[1], plane[2]);
    
    const PointF& rp = r.getPos();
    float dotNormalRayDir = Math::dot3(normal, r.getDir());
    
    // Is the ray perpendicular to the plane's normal?
    if (fabs(dotNormalRayDir) < PLANE_INTERSECTION_THRESHOLD) {
        return false;
    }
    
    // Determine which side of the plane the point is on
    float distFromPlane = Math::dot3(normal, rp) + plane[3];
    float t = distFromPlane/dotNormalRayDir;
    
    // > 0 if ray and normal are in the same direction and
    // the ray is on the normal side of the plane or
    // If the ray and normal point in opposite directions and
    // the ray is not on the normal side of the plane
    if (t > 0) {
        return false;
    }
    
    intersection = Math::vec3AXPlusB(r.getDir(), -t, r.getPos());
    return true;
}
    
}
}
