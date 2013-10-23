//
//  Quat.c
//  Renderer
//
//  Created by Benjamin Gregorski on 9/17/13.
//
//

#include <stdio.h>
#include "Quat.h"
#include "BasicTypesImpl.h"

namespace Framework { namespace Math {
 
    Quat::Quat() : m_s(1), m_v() {}
    
    Quat::Quat(const float s, const float x, const float y, const float z)
    : m_s(s), m_v(x,y,z) {}
    
    Quat::Quat(const float scalar, const VectorF& vector) : m_s(scalar), m_v(vector){}
    Quat::Quat(const Quat& q) : m_s(q.m_s), m_v(q.m_v) {}
    
    Quat& Quat::operator=(const Framework::Math::Quat &q) {
        if (this == &q) {
            return (*this);
        }
        
        m_s = q.m_s;
        m_v = q.m_v;
        return (*this);
    }
    
    Quat& Quat::operator*=(const Framework::Math::Quat &q) {
        VectorF c = cross(m_v, q.m_v);
        VectorF v0 = vec3AXPlusBY(q.m_v, m_s, m_v, q.m_s);
        
        m_s = q.m_s * m_s - dot3(m_v, q.m_v);
        
        //(a * q1.vect) + (q1.a * vect) + cross( vect , q1.vect ) ;
        m_v = vec3APlusB(v0, c);
        
        return *this ;
    }
    
    void Quat::extractAngleAndVector(float& angle, VectorF& v) const {
        // m_s stores cos(angle/2)
        angle = acosf(m_s)*2.0f;
        
        // m_v stores sin(angle/2)*v
        float vecScale = 1.0f/sinf(angle*0.5);
        v = vec3Scale(m_v, vecScale);
    }
    
    void Quat::set(const float s, const float x, const float y, const float z) {
        m_s = s;
        m_v.set(x,y,z);
    }
    
    void Quat::setRotation(const float angle, const VectorF &v, const AngleType angleType) {
        float cp, sp;
        if (DEGREES == angle) {
            float radians = (angle * M_PI / 180.0f)*0.5f;
            cp = cos(radians);
            sp = sin(radians);
        } else {
            cp = cos(angle*0.5f);
            sp = sin(angle*0.5f);
        }
        
        m_s = cp;
        m_v = vec3Scale(v, sp);
    }
    
    float Quat::length() const {
        return (sqrt(m_s*m_s + vec3FastLen(m_v)));
    }
    
    float Quat::fastLength() const {
        return (m_s*m_s + vec3FastLen(m_v));
    }
    
    void Quat::normalize() {
        float l = length();
        
        if (0.0 == l) {
            return;
        }
        
        l = 1.0f/l;
        m_s *= l;
        m_v.scale(l);
    }
    
    Quat Quat::inverse() const {
        Quat qq;
        float l = fastLength();
        if (0 == l) {
            return qq;
        }
        
        l = 1.0f/(l);
        
        qq.m_s = (m_s)*l;
        qq.m_v = vec3Scale(m_v, -l);
        return qq;
    }
    
    Matrix44 Quat::getMatrix() const {
        Matrix44 m;
        m.m[0][0] = 1.0 - 2.0*(y()*y() + z()*z());
        m.m[0][1] = 2.0*(x()*y() - z()*s());
        m.m[0][2] = 2.0*(z()*x() + y()*s());
        m.m[0][3] = 0.0;
        
        m.m[1][0] = 2.0*(x()*y() + z()*s());
        m.m[1][1] = 1.0 - 2.0*(z()*z() + x()*x());
        m.m[1][2] = 2.0*(y()*z() - x()*s());
        m.m[1][3] = 0.0;
        
        m.m[2][0] = 2.0*(z()*x() - y()*s());
        m.m[2][1] = 2.0*(y()*z() + x()*s());
        m.m[2][2] = 1.0 - 2.0*(y()*y() + x()*x());
        m.m[2][3] = 0.0;
        
        m.m[3][0] = 0.0 ;
        m.m[3][1] = 0.0 ;
        m.m[3][2] = 0.0 ;
        m.m[3][3] = 1.0 ;
        
        /*a[0][0] = 1.0 - 2.0 *( vect.y() * vect.y() + vect.z() * vect.z() ) ;
        a[0][1] = 2.0 * ( vect.x() * vect.y() - vect.z() * r() ) ;
        a[0][2] = 2.0 * ( vect.z() * vect.x()
                         + vect.y() * r() ) ;
        a[0][3] = 0.0 ;
        
        a[1][0] = 2.0 * ( vect.x() * vect.y()
                         + vect.z() * r() ) ;
        a[1][1] = 1.0 - 2.0 * ( vect.z() * vect.z()
                               + vect.x() * vect.x() ) ;
        a[1][2] = 2.0 * ( vect.y() * vect.z()
                         - vect.x() * r() ) ;
        a[1][3] = 0.0 ;
        
        a[2][0] = 2.0 * ( vect.z() * vect.x()
                         - vect.y() * r() ) ;
        a[2][1] = 2.0 * ( vect.y() * vect.z()
                         + vect.x() * r() ) ;
        a[2][2] = 1.0 - 2.0 * ( vect.y() * vect.y()
                               + vect.x() * vect.x() ) ;
        a[2][3] = 0.0 ;
        
        a[3][0] = 0.0 ;
        a[3][1] = 0.0 ;
        a[3][2] = 0.0 ;
        a[3][3] = 1.0 ;*/
        
        return m;
    }
    
    bool Quat::isZero() const {
        return (0.0 == s() && m_v.isZero());
    }
    
}
}

