//
//  Trackball.h
//  Renderer
//
//  Created by Benjamin Gregorski on 9/25/13.
//
//

#ifndef __Renderer__Trackball__
#define __Renderer__Trackball__

#include <iostream>
#include "Quat.h"
#include "BasicTypes.h"

namespace Framework { namespace Math {
    /**
     * The Trackball class models a sphere centered at the origin 
     * used to create Quaterion rotations.
     *
     * A 2D point in the space [-1,1]. [-1,1] is projected onto the sphere
     * and selects a point on the Trackball. Successive point selections are used
     * to create a rotation between the two points on the sphere.
     *
     */
    class Trackball {
    public:
        Trackball(const float radius = 1.0f);
        
        void setRadius(const float r) { m_radius = r; }
        
        const Quat& getCurrentRotation() const { return m_currentRotation; }
        
        void initialize(const float x, const float y);
        
        /**
         * Update the current rotation using the indicate (x,y) position
         * to find the projection on the sphere and create a rotation
         * between the new point and the current point.
         *
         */
        void updateRotation(const float x, const float y);
        
        void disable() { m_currentState = DISABLED; }
        
        /**
         * Reset prev and current rotations to a 0 degree rotation.
         */
        void reset();
        
        /**
         * Given an (x,y) position in [-1,1] project to a point on the
         * trackball sphere.
         */
        PointF projectToSphere(const float x, const float y) const;
        
    protected:
        
    private:
        enum TrackballState {
            DISABLED = 0,
            ENABLED = 1,
        };
        
        TrackballState m_currentState;
        float m_radius;
        
        PointF m_prevPoint;
        PointF m_currentPoint;
        
        Quat m_currentRotation;
    };
}
}


#endif /* defined(__Renderer__Trackball__) */
