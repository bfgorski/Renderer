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
}