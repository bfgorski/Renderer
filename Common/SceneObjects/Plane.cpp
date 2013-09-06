//
//  Plane.cpp
//  Renderer
//
//  Created by Benjamin Gregorski on 8/30/13.
//
//

#include <iostream>
#include "Plane.h"
#include "BasicTypesImpl.h"

#define PLANE_PERPENDICULAR_THRESHOLD 0.0001

using namespace Framework;

Plane::Plane(const PointF& p, const VectorF& n, const bool normalize) : m_point(p), m_normal(n) {
    if (normalize) {
        Math::vec3Normalize(m_normal);
    }
    
    calcEq();
}

Plane::Plane(const Plane& p) : m_point(p.m_point), m_normal(p.m_normal) { calcEq(); }

Plane& Plane::operator=(const Framework::Plane &p) {
    if (this == &p) {
        return (*this);
    }
    
    m_normal = p.m_normal;
    m_point = p.m_point;
    calcEq();
    
    return (*this);
}

void Plane::calcEq() {
    // Store D component of Ax + By + Cz + D = 0
    m_D = - Math::dot3(m_normal, m_point);
}

SOIntersectionType Plane::intersect(const Ray& r, SOIntersection* intersectionInfo) const {
    PointF intersectionPoint;
    SOIntersectionType intersectionType = planeIntersect(r, intersectionPoint);
    
    if (intersectionInfo) {
        intersectionInfo->set(this, intersectionPoint, m_normal, intersectionType);
    }
    
    return intersectionType;
}

SOIntersectionType Plane::intersect(const Ray& r, PointF& intersectionPoint) const {
    return (planeIntersect(r, intersectionPoint));
}


SOIntersectionType Plane::planeIntersect(const Ray &r, PointF &intersectionPoint) const {
    const PointF& rp = r.getPos();
    float dotNormalRayDir = Math::dot3(m_normal, r.getDir());
    
    // Is the ray perpendicular to the plane's normal?
    if (fabs(dotNormalRayDir) < PLANE_PERPENDICULAR_THRESHOLD) {
        return SOIntersectionNone ;
    }
    
    // Determine which side of the plane the point is on
    float distFromPlane = Math::dot3(m_normal, rp) + m_D ;
    float t = distFromPlane/dotNormalRayDir ;
    
    // > 0 if ray and normal are in the same direction and
    // the ray is on the normal side of the plane or
    // If the ray and normal point in opposite directions and
    // the ray is not on the normal side of the plane
    if (t > 0) {
        return (SOIntersectionNone) ;
    }
    
    SOIntersectionType intersectionType;
    
    /*
     The normal side of the plane is considered "inside"
     */
    if (dotNormalRayDir < 0) {
        intersectionType = SOIntersectionLeaving;
    } else {
        intersectionType = SOIntersectionEntering;
    }
    
    intersectionPoint = Math::vec3AXPlusB(r.getDir(), -t, r.getPos());
    return intersectionType;
}



