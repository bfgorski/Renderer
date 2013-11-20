//
//  Plane.cpp
//  Renderer
//
//  Created by Benjamin Gregorski on 8/30/13.
//
//

#include "Plane.h"
#include "BasicTypesImpl.h"
#include "SOCreateGeoArgs.h"

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

void Plane::createGeo(const SOCreateGeoArgs *args) {
    PolygonMesh& pm = createPolygonMesh();
    
    float width = 5;
    float height = 5;
    
    // number of points in each direction
    int uSize = 5;
    int vSize = 5;
    
    if (args) {
        uSize = args->getTessFactor(CREATE_GEO_TESS_FACTOR_U);
        vSize = args->getTessFactor(CREATE_GEO_TESS_FACTOR_V);
    }
    
    pm.init((uSize-1)*(vSize-1)*2, (uSize*vSize), PolygonMesh::PosNorm);
   
    VectorF uAxis;
    VectorF vAxis;
    
    Math::createAxes(m_normal, uAxis, vAxis);
    
    VectorF v = Math::vec3AXPlusBY(uAxis, width/2.0f, vAxis, height/2.0f);
    VectorF uOffset = Math::vec3Scale(uAxis, width/(uSize-1));
    VectorF vOffset = Math::vec3Scale(vAxis, width/(vSize-1));
    
    PointF start = Math::vec3APlusB(m_point, v);
    
    // Position and normal
    float vertData[6];
    
    vertData[3] = m_normal.x();
    vertData[4] = m_normal.y();
    vertData[5] = m_normal.z();
    
    // Create vertices
    for (int row = 0; row < vSize; ++row) {
        vertData[0] = start.x();
        vertData[1] = start.y();
        vertData[2] = start.z();
        pm.addVertices(vertData, 1);
        
        for (int col = 1; col < uSize; ++col) {
            vertData[0] += uOffset.x()*col;
            vertData[1] += uOffset.y()*col;
            vertData[2] += uOffset.z()*col;
            
            pm.addVertices(vertData, 1);
        }
        
        start.increment(vOffset);
    }
    
    unsigned int t[6];
    
    // create triangles
    for (int row = 0; row < (vSize-1); ++row) {
        unsigned int rowOffset = row*uSize;
        
        /*
          t[0] ... t[2]
          .
          .
          t[1] ... t[5]
        */
        
        for (int col = 0; col < (uSize-1); ++col) {
            t[0] = rowOffset + col;
            t[1] = rowOffset + uSize + col;
            t[2] = t[0] + 1;
            
            t[3] = t[2];
            t[4] = t[1];
            t[5] = t[1] + 1;
            pm.addTriangles(t, 2);
        }
        
        start.increment(vOffset);
    }
}






















