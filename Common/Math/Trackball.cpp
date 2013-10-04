//
//  Trackball.cpp
//  Renderer
//
//  Created by Benjamin Gregorski on 9/25/13.
//
//

#include "Trackball.h"
#include "BasicTypes.h"
#include "BasicTypesImpl.h"

namespace Framework { namespace Math {
    
    Trackball::Trackball(const float radius)
    : m_currentState(DISABLED), m_radius(radius), m_prevPoint(0,0,1), m_currentPoint(0,0,1), m_currentRotation(1,VZero)
    {
    }
    
    void Trackball::initialize(const float x, const float y) {
        // If the trackball was disabled update prev/cur points by don't clear the transform
        m_currentState = ENABLED;
        m_prevPoint = projectToSphere(x, y);
        m_prevPoint.normalize();
        m_currentPoint = m_prevPoint;
    }
    
    void Trackball::updateRotation(const float x, const float y) {
        if (DISABLED == m_currentState) {
            return;
        } else {
            PointF projectedPoint = projectToSphere(x, y);
            projectedPoint.normalize();
            
            // Early out if rotation vector will be 0.
            if (isEqual(projectedPoint, m_currentPoint)) {
                return;
            }
            
            VectorF rotateVector = cross(m_currentPoint, projectedPoint);
            
            if (0.001 > vec3FastLen(rotateVector)) {
                return;
            }
            
            m_prevPoint = m_currentPoint;
            m_currentPoint = projectedPoint;
            
            Quat inv = m_currentRotation.inverse();
            Math::Matrix44 m = inv.getMatrix();
            rotateVector = m.applyToVector(rotateVector);
            rotateVector.clamp(0.01);
            
            // treat as vectors to the origin and get a vector to rotate around
            rotateVector.normalize();
            
            // multiply by 0.1 instead of 0.5 to slow down the rotation
            float rotateAngle = acos(dot3(m_prevPoint, m_currentPoint))*0.5;
            rotateVector.scale(sin(rotateAngle));
            
            printf("RV %f, (%f,%f,%f)\n", rotateAngle, rotateVector.v[0], rotateVector.v[1], rotateVector.v[2]);
            
            Quat newRotation(cos(rotateAngle), rotateVector);
            newRotation.normalize();
            
            float angle;
            VectorF vNew;
            
            newRotation.extractAngleAndVector(angle, vNew);
            angle = (angle*180/M_PI);
            printf("New %f, (%f,%f,%f)\n", angle, vNew.v[0], vNew.v[1], vNew.v[2]);
            
            m_currentRotation.extractAngleAndVector(angle, vNew);

            angle = (angle*180/M_PI);
            printf("Cur %f, (%f,%f,%f)\n", angle, vNew.v[0], vNew.v[1], vNew.v[2]);
            
            m_currentRotation *= newRotation;
            
            m_currentRotation.extractAngleAndVector(angle, vNew);
            
            angle = (angle*180/M_PI);
            printf("Final %f, (%f,%f,%f)\n", angle, vNew.v[0], vNew.v[1], vNew.v[2]);
            
            m_currentRotation.normalize();
        }
    }
    
    void Trackball::reset() {
        m_currentState = DISABLED;
        m_currentRotation.setRotation(0, VZero);
    }
    
    /*
     float z, d, t ;
     
     float x1 = x ;
     float y1 = y ;
     
     d = sqrt( x1*x1 + y1*y1 ) ;
     if ( d < _trackball_size*M_SQRT1_2 ) {
     z = sqrt( _trackball_size*_trackball_size - d*d ) ;
     }
     else {
     t = _trackball_size / M_SQRT2 ;
     z = t*t / d ;
     //z = r*r / ( 2.0 * d ) ;
     }

     
     */
    
    PointF Trackball::projectToSphere(const float x, const float y) const {
        // take the point (x,y,1) and project onto the sphere centered at (0,0,0)
        float d = (x*x + y*y); // distance to center
        float z = 0;
        
        // Point is on the sphere
        if (d <= m_radius*m_radius) {
            z = sqrt(m_radius*m_radius - d);
        } else {
            // out side of sphere z is 0
        }
    
        return PointF(x,y,z);
     }
}
}
