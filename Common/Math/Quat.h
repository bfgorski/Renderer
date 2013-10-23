//
//  Quat.h
//  Renderer
//
//  Created by Benjamin Gregorski on 9/17/13.
//
//

#ifndef Renderer_Quat_h
#define Renderer_Quat_h

#include "BasicTypes.h"
#include "Matrix.h"

namespace Framework { namespace Math {
    struct Quat {
        float m_s;
        VectorF m_v;
        
        /**
         * Set to all zeros.
         */
        Quat();
        Quat(const float s, const float x, const float y, const float z);
        Quat(const float s, const VectorF& v);
        Quat(const Quat& q);
        Quat& operator=(const Quat&q);
        
        Quat& operator*=(const Quat& q);
        Quat& operator*=(const float f);
        
        float s() const { return m_s; }
        float x() const { return m_v.v[XAxis]; }
        float y() const { return m_v.v[YAxis]; }
        float z() const { return m_v.v[ZAxis]; }
        
        /**
         * Set scale and vector components directly.
         */
        void set(const float s, const float x, const float y, const float z);
        
        /**
         * Set to rotation about the indicated vector
         *
         * @param angle Angle in degrees
         */
        void setRotation(const float angle, const VectorF& v, const AngleType angleType = DEGREES);
        
        /**
         * Return the rotation angle and vector.
         */
        void extractAngleAndVector(float& angle, VectorF& v) const;
        
        float length() const;
        
        /**
         * Squared length to avoid sqrt operation.
         */
        float fastLength() const;
        
        void normalize();
        Quat inverse() const;
        Matrix44 getMatrix() const;
        
        /**
         * Check if all of the components are 0.
         */
        bool isZero() const;
    };
    
    typedef struct Quat Quat;
    
    /**
     * Return q1*q2
     */
    Quat mult(const Quat& q1, const Quat * q2);
}
}



#endif
