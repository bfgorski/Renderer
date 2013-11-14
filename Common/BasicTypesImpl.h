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

/**
 * Color Calculations
 */
    
/**
 * Calculate final lit color from diffuse, spec and ambient lighting
 * for RGB channels. Alpha is set to surfaceDiffuse alpha.
 */
Color lightSurface(
    const Color& lightDiffuse, const Color& surfaceDiffuse,
    const Color& lightSpec, const Color& surfaceSpec,
    const Color& lightAmb, const Color& surfaceAmb);
    
/**
 * Component wise comparison
 */
bool isEqual(const vec3&, const vec3&, const float delta = 0);
    
float vec3Len(const vec3& v);
float vec3Len(const vec4& v);
float vec4Len(const vec4& v);

/**
 * Return the length squared.
 */
float vec3FastLen(const vec3& v);
    
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
    
/**
 * Intersect a Ray with a plane defined by a point and a normal.
 *
 * @param r             The Ray to intersect with the plane
 * @param point         A point on the plane
 * @param normal        The plane normal.
 * @param intersection  Return the itersection point here.
 *                      Undefined if false is returned.
 * @return true/false   Indicating if the Ray intersects the plane.
 */
bool planeIntersect(const Ray& r, const PointF& point, const VectorF& normal, PointF& intersection);

/**
 * Intersect a Ray with a plane defined by the equation Ax + By + Cz + D = 0.
 *
 * @param r             The Ray to intersect with the plane
 * @param plane         An array of 4 floats for the plane equation .
 * @param intersection  Return the itersection point here.
 *                      Undefined if false is returned.
 *
 * @return true/false   Indicating if the Ray intersects the plane.
 */
bool planeIntersect(const Ray& r, const float *plane, PointF& intersection);
    
}
}
#endif
