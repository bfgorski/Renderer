//
//  Plane.h
//  Renderer
//
//  Created by Benjamin Gregorski on 8/30/13.
//
//

#ifndef __Renderer__Plane__
#define __Renderer__Plane__

#include "SceneObject.h"
#include "BasicTypes.h"

namespace Framework {
    
    class Plane : public SceneObject {
        public :
        
        enum PlaneLocation {
            PlaneBelow = -1, // Point is on the opposite side of the normal direction
            PlaneOn = 0,     // Point is on the plane
            PlaneAbove = 1   // Point is on the side of the normal direction
        };
        
        /**
         * Construct a Plane from a point and a normal vector.
         * The vector is assumed to be normalized.
         */
        Plane(const PointF& p, const VectorF& n, const bool normalize = false);
        Plane(const Plane&p);
        Plane& operator=(const Plane& p);
        
        const PointF& getPoint() const { return m_point; }
        const VectorF& getNormal() const { return m_normal; }
        
        void setPoint(const PointF& p) { m_point = p; }
        void setNormal(const VectorF& v) { m_normal = v; }
        
        PlaneLocation locate(const PointF& p);
        
        /**
         * Determine if the indicated Ray intersects the object.
         */
        virtual SOIntersectionType intersect(const Ray& r, SOIntersection* intersectionInfo) const;
        
        /**
         * Determine if the indicated Ray intersects the object
         * and get the intersection point only.
         */
        virtual SOIntersectionType intersect(const Ray& r, PointF& intersectionPoint) const;
        
    protected:
        
        /**
         * Cache coefficients for plane equation.
         */
        void calcEq();
        
        SOIntersectionType planeIntersect(const Ray& r, PointF& intersectionPoint) const;
    private:
        PointF m_point;
        VectorF m_normal;
        
        // Storage for D component in Ax + By + Cz + D = 0;
        float m_D;
    };
}

#endif /* defined(__Renderer__Plane__) */
