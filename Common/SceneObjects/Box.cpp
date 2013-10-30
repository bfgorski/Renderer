//
//  Box.cpp
//  Renderer
//
//  Created by Benjamin Gregorski on 10/2/13.
//
//

#include "Box.h"

namespace Framework {
    Box::Box() : m_diagStart(-0.5,-0.5,-0.5), m_diagEnd(0.5,0.5,0.5){
        
    }
    
    Box::Box(const PointF& p0, const PointF& p1) : m_diagStart(p0), m_diagEnd(p1) {}
    
    void Box::applyTransform(const Math::Transform &t) {
        
    }
    
    SOIntersectionType Box::intersect(const Ray& r, SOIntersection* intersectionInfo) const {
        return SOIntersectionNone;
    }
    
    SOIntersectionType Box::intersect(const Ray& r, PointF& intersectionPoint) const {
        return SOIntersectionNone;
    }
    
    void Box::createGeo(const SOCreateGeoArgs *args) {
        static const unsigned int boxTriangles[] = { 0,2,1, 1,2,3, 5,1,3, 5,3,7, 7,3,2, 2,6,7, 4,2,0, 6,2,4, 4,7,6, 4,5,7, 4,0,5, 0,1,5 };
        
        static_assert( (sizeof(boxTriangles) == (36*sizeof(unsigned int))), "Box triangle indices are incorrect" );
        
        PolygonMesh& pm = createPolygonMesh();
        pm.init(8, 12, PolygonMesh::PosNorm);
        pm.addTriangles(boxTriangles, 12);
    
        // Vertex 0 is diag start, vertex 7 is diag end
        float x = m_diagEnd.x() - m_diagStart.x();
        float y = m_diagEnd.y() - m_diagStart.y();
        float z = m_diagEnd.z() - m_diagStart.z();
        
        float cx = m_diagStart.x() + 0.5*x;
        float cy = m_diagStart.y() + 0.5*x;
        float cz = m_diagStart.z() + 0.5*x;
        
        float v[6]; // 3 pos, 3 norm
        
        for (int i = 0; i < 7; ++i) {
            float hasX = float(i&0x1);
            float hasY = float(i&0x2);
            float hasZ = float(i&0x4);
            
            v[0] = m_diagStart.x() + x*hasX;
            v[1] = m_diagStart.y() + y*hasY;
            v[2] = m_diagStart.z() + z*hasZ;
            
            vec3 n = vec3(v[0]-cx, v[1]-cy, v[2]-cz);
            n.normalize();
            v[3] = n.x();
            v[4] = n.y();
            v[5] = n.z();
            
            pm.addVertices(reinterpret_cast<const void*>(v), 1);
        }
        
    }
}