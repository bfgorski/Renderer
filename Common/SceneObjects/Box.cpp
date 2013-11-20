//
//  Box.cpp
//  Renderer
//
//  Created by Benjamin Gregorski on 10/2/13.
//
//

#include "Box.h"
#include "BasicTypesImpl.h"

namespace Framework {
    Box::Box() : m_frame(PointF(0,0,0), VectorF(1,0,0), VectorF(0,1,0), VectorF(0,0,1)){
        // Store dimension as the distance from the center to the box boundary
        m_dimensions[0] = m_dimensions[1] = m_dimensions[2] = 0.5f;
    }
    
    Box::Box(const Frame& f, const float uDim, const float vDim, const float wDim) : m_frame(f) {
        m_dimensions[0] = uDim*0.5;
        m_dimensions[1] = vDim*0.5;
        m_dimensions[2] = wDim*0.5;
    }
    
    bool Box::isInside(const PointF &p, const bool onIsIn) const {
        // Take the dot product of the Vector from the box center to the point in question
        // against the three vectors of the coordinate frame
        VectorF pointToCenter = Math::vec3AMinusB(p, m_frame.origin());
        
        if (onIsIn) {
            float d = fabs(Math::dot3(pointToCenter, m_frame.u()));
            if (d > m_dimensions[0]) {
                return false;
            }
            
            d = fabs(Math::dot3(pointToCenter, m_frame.v()));
            if (d > m_dimensions[1]) {
                return false;
            }
            
            d = fabs(Math::dot3(pointToCenter, m_frame.w()));
            if (d > m_dimensions[2]) {
                return false;
            }
        } else {
            float d = fabs(Math::dot3(pointToCenter, m_frame.u()));
            if (d >= m_dimensions[0]) {
                return false;
            }
            
            d = fabs(Math::dot3(pointToCenter, m_frame.v()));
            if (d >= m_dimensions[1]) {
                return false;
            }
            
            d = fabs(Math::dot3(pointToCenter, m_frame.w()));
            if (d >= m_dimensions[2]) {
                return false;
            }

        }
        return true;
    }
    
    void Box::applyTransform(const Math::Transform &t) {
        // Apply transform to frame and calculate new dimensions
    }
    
    void Box::intersectionHelper(
                                 const Ray& r,
                                 const PointF& p,
                                 const VectorF& n,
                                 const VectorF& dir0,
                                 const float size0,
                                 const VectorF& dir1,
                                 const float size1,
                                 PointF& closestIntersection,
                                 VectorF& closestNormal,
                                 float& closestDistance
                                 ) const {
        
        PointF intersection;
        if (Math::planeIntersect(r, p, n, intersection)) {
            
            VectorF pointToCenter = Math::vec3AMinusB(intersection, p);
            
            // Check that the intersection is inside the box face represented by
            // (dir0, size0) and (dir1,size1)
            float d = fabs(Math::dot3(pointToCenter, dir0));
            
            if (d > size0) {
                return;
            }
            
            d = fabs(Math::dot3(pointToCenter, dir1));
            
            if (d > size1) {
                return;
            }
            
            d = Math::vec3FastDist(r.getPos(), intersection);
            if (d < closestDistance) {
                closestDistance = d;
                closestIntersection = intersection;
                closestNormal = n;
            }
        }
    }
    
    SOIntersectionType Box::findIntersection(const Ray& r, PointF& closestIntersection, VectorF& closestNormal) const {
        PointF intersection;
        float closestDistance = 1e6;
        
        // Intersection 6 planes and see which comes first
        // -U face
        PointF faceCenter = Math::vec3AXPlusB(m_frame.u(), -m_dimensions[0], m_frame.origin());
        VectorF faceNormal = Math::vec3Scale(m_frame.u(), -1);
        
        intersectionHelper(r, faceCenter, faceNormal, m_frame.v(), m_dimensions[1], m_frame.w(), m_dimensions[2], closestIntersection, closestNormal, closestDistance);
        
        // U face
        faceCenter = Math::vec3AXPlusB(m_frame.u(), m_dimensions[0], m_frame.origin());
        intersectionHelper(r, faceCenter, m_frame.u(), m_frame.v(), m_dimensions[1], m_frame.w(), m_dimensions[2], closestIntersection, closestNormal, closestDistance);
        
        // -V face
        faceCenter = Math::vec3AXPlusB(m_frame.v(), -m_dimensions[1], m_frame.origin());
        faceNormal = Math::vec3Scale(m_frame.v(), -1);
        intersectionHelper(r, faceCenter, faceNormal, m_frame.u(), m_dimensions[0], m_frame.w(), m_dimensions[2], closestIntersection, closestNormal, closestDistance);
        
        // V face
        faceCenter = Math::vec3AXPlusB(m_frame.v(), m_dimensions[1], m_frame.origin());
        intersectionHelper(r, faceCenter, m_frame.v(), m_frame.u(), m_dimensions[0], m_frame.w(), m_dimensions[2], closestIntersection, closestNormal, closestDistance);
        
        // -W face
        faceCenter = Math::vec3AXPlusB(m_frame.w(), -m_dimensions[2], m_frame.origin());
        faceNormal = Math::vec3Scale(m_frame.w(), -1);
        intersectionHelper(r, faceCenter, faceNormal, m_frame.u(), m_dimensions[0], m_frame.v(), m_dimensions[1], closestIntersection, closestNormal, closestDistance);
        
        // W face
        faceCenter = Math::vec3AXPlusB(m_frame.w(), m_dimensions[2], m_frame.origin());
        intersectionHelper(r, faceCenter, faceNormal, m_frame.u(), m_dimensions[0], m_frame.v(), m_dimensions[1], closestIntersection, closestNormal, closestDistance);
        
        if (1e6 != closestDistance) {
            return ((Math::dot3(r.getDir(), closestNormal) > 0) ? SOIntersectionLeaving : SOIntersectionEntering);
        }
        
        return SOIntersectionNone;
    }
    
    SOIntersectionType Box::intersect(const Ray& r, SOIntersection* intersectionInfo) const {
        PointF closestIntersection;
        VectorF closestNormal;

        SOIntersectionType t = findIntersection(r, closestIntersection, closestNormal);

        if (intersectionInfo && (SOIntersectionNone != t)) {
            intersectionInfo->setPoint(closestIntersection);
            intersectionInfo->setNormal(closestNormal);
            intersectionInfo->setObject(this);
            intersectionInfo->setType(t);
        }
        
        return t;
    }
    
    SOIntersectionType Box::intersect(const Ray& r, PointF& intersectionPoint) const {
        VectorF closestNormal;
        return findIntersection(r, intersectionPoint, closestNormal);
    }
    
    void Box::createGeoHelper(const PointF& fc, const VectorF& fn, const VectorF& v0, const float v0S, const VectorF& v1, const float v1S, float * v) {
        for (int i = 0; i < 4; ++i, v+=6) {
            float v0Scale = (i & 0x1) ? v0S : -v0S;
            float v1Scale = (i & 0x2) ? v1S : -v1S;
            
            v[0] = fc.x() + v0.x()*v0Scale + v1.x()*v1Scale;
            v[1] = fc.y() + v0.y()*v0Scale + v1.y()*v1Scale;
            v[2] = fc.z() + v0.z()*v0Scale + v1.z()*v1Scale;
            v[3] = fn.x();
            v[4] = fn.y();
            v[5] = fn.z();
        }
    }
    
    void Box::createGeo(const SOCreateGeoArgs *args) {
        
        // Create 12 triangles from 24 vertices each with a distinct normal
        static const unsigned int boxTriangles[] = {
            0,2,1,      1,2,3,      // -U face
            4,6,5,      5,6,7,      //  U face
            8,10,9,     9,10,11,    // -V face
            12,14,13,   13,14,15,   //  V face
            16,18,17,   17,18,19,   // -W face
            20,22,21,   21,22,23    //  W face
        };
        
        //static_assert( (sizeof(boxTriangles) == (36*sizeof(unsigned int))), "Box triangle indices are incorrect" );
        
        // 24 vertices, 12 triangles
        PolygonMesh& pm = createPolygonMesh();
        pm.init(24, 12, PolygonMesh::PosNorm);
        pm.addTriangles(boxTriangles, 12);
        pm.setNumVertices(24);
        
        float *v = reinterpret_cast<float*>(pm.getRawVerts()); // space for 4 positions and 4 normal vectors
        
        // -U face
        PointF faceCenter = Math::vec3AXPlusB(m_frame.u(), -m_dimensions[0], m_frame.origin());
        VectorF faceNormal = Math::vec3Scale(m_frame.u(), -1);
        createGeoHelper(faceCenter, faceNormal, m_frame.v(), m_dimensions[1], m_frame.w(), m_dimensions[2], v);
        v += 24;
        
        // U face
        faceCenter = Math::vec3AXPlusB(m_frame.u(), m_dimensions[0], m_frame.origin());
        createGeoHelper(faceCenter, m_frame.u(), m_frame.v(), m_dimensions[1], m_frame.w(), m_dimensions[2], v);
        v += 24;
        
        // -V face
        faceCenter = Math::vec3AXPlusB(m_frame.v(), -m_dimensions[1], m_frame.origin());
        faceNormal = Math::vec3Scale(m_frame.v(), -1);
        createGeoHelper(faceCenter, faceNormal, m_frame.u(), m_dimensions[0], m_frame.w(), m_dimensions[2], v);
        v += 24;
        
        // V face
        faceCenter = Math::vec3AXPlusB(m_frame.v(), m_dimensions[1], m_frame.origin());
        createGeoHelper(faceCenter, m_frame.v(), m_frame.u(), m_dimensions[0], m_frame.w(), m_dimensions[2], v);
        v += 24;
        
        // -W face
        faceCenter = Math::vec3AXPlusB(m_frame.w(), -m_dimensions[2], m_frame.origin());
        faceNormal = Math::vec3Scale(m_frame.w(), -1);
        createGeoHelper(faceCenter, faceNormal, m_frame.u(), m_dimensions[0], m_frame.v(), m_dimensions[1], v);
        v += 24;
        
        // W face
        faceCenter = Math::vec3AXPlusB(m_frame.w(), m_dimensions[2], m_frame.origin());
        createGeoHelper(faceCenter, m_frame.w(), m_frame.u(), m_dimensions[0], m_frame.v(), m_dimensions[1], v);
    }
}













