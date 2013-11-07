//
//  Transform.c
//  Renderer
//
//  Created by Benjamin Gregorski on 9/17/13.
//
//

#include <stdio.h>
#include "Transform.h"
#include "BasicTypesImpl.h"

namespace Framework { namespace Math {
    
    Transform translateBy(const VectorF& v) {
        Transform t ;
        t.set(3,0,v.v[0]);
        t.set(3,1,v.v[1]);
        t.set(3,2,v.v[2]);
        return t;
    }
    
    Transform translateBy(const float x, const float y, const float z) {
        Transform t ;
        t.set(3,0,x);
        t.set(3,1,y);
        t.set(3,2,z );
        return t;
    }
    
    Transform rotateX(const float angle, const AngleType angleType) {
        float cp, sp;
        
        if (DEGREES == angleType) {
            cp = cos (angle * M_PI / 180.0) ;
            sp = sin (angle * M_PI / 180.0) ;
        } else {
            cp = cos(angle);
            sp = cos(angle);
        }
        
        Transform t;
        t.set(1,1,cp);
        t.set(1,2,sp);
        t.set(2,1,-sp);
        t.set(2,2,cp);
        return t;
    }
    
    Transform rotateY(const float angle, const AngleType angleType) {
        float cp, sp;
        
        if (DEGREES == angleType) {
            cp = cos (angle * M_PI / 180.0) ;
            sp = sin (angle * M_PI / 180.0) ;
        } else {
            cp = cos(angle);
            sp = cos(angle);
        }
        
        Transform t;
        t.set(0,0,cp);
        t.set(0,2,-sp);
        t.set(2,0,sp);
        t.set(2,2,cp);
        return t;
    }
    
    Transform rotateZ(const float angle, const AngleType angleType) {
        float cp, sp;
        
        if (DEGREES == angleType) {
            cp = cos (angle * M_PI / 180.0) ;
            sp = sin (angle * M_PI / 180.0) ;
        } else {
            cp = cos(angle);
            sp = cos(angle);
        }

        Transform t;
        t.set(0,0,cp);
        t.set(0,1,sp);
        t.set(1, 0, -sp);
        t.set(1, 1, cp);
        return t;
    }

    Transform frameToFrame(const Frame& f1, const Frame& f2) {
        Transform t1 ;
        
        // This takes point in f1 and moves it to the Cartesian Frame
        t1.m[0][0] = f1.u().v[XAxis];
        t1.m[0][1] = f1.u().v[YAxis];
        t1.m[0][2] = f1.u().v[ZAxis];
        
        t1.m[1][0] = f1.v().v[XAxis];
        t1.m[1][1] = f1.v().v[YAxis];
        t1.m[1][2] = f1.v().v[ZAxis];
        
        t1.m[2][0] = f1.w().v[XAxis];
        t1.m[2][1] = f1.w().v[YAxis];
        t1.m[2][2] = f1.w().v[ZAxis];
        
        t1.m[3][0] = f1.origin().v[XAxis];
        t1.m[3][1] = f1.origin().v[YAxis];
        t1.m[3][2] = f1.origin().v[ZAxis];
        
        Transform t2 ;
        VectorF t ;
        
        float d = 1.0f / dot3(f2.u(), cross (f2.v(), f2.w())) ;
        
        t = VectorF( 1.0, 0.0, 0.0 ) ;
        
        VectorF crossVW = cross(f2.m_v, f2.w());
        VectorF crossTW = cross(t, f2.w());
        VectorF crossVT = cross(f2.v(), t);
        
        t2.m[0][0] = dot3(t, crossVW) * d ;
        t2.m[0][1] = dot3(f2.u(), crossTW) * d ;
        t2.m[0][2] = dot3(f2.u(), crossVT) * d ;
        
        t = VectorF( 0.0, 1.0, 0.0 ) ;
        
        t2.m[1][0] = dot3(t, crossVW) * d ;
        t2.m[1][1] = dot3(f2.u(), crossTW) * d ;
        t2.m[1][2] = dot3(f2.u(), crossVT) * d ;
        
        t = VectorF( 0.0, 0.0, 1.0 ) ;
        
        t2.m[2][0] = dot3(t, crossVW) * d ;
        t2.m[2][1] = dot3(f2.u(), crossTW) * d ;
        t2.m[2][2] = dot3(f2.u(), crossVT) * d ;
        
        t = PointF(-f2.origin().v[0], -f2.origin().v[1], -f2.origin().v[2]);
        
        t2.m[3][0] = dot3(t, crossVW) * d ;
        t2.m[3][1] = dot3(f2.u(), crossTW) * d ;
        t2.m[3][2] = dot3(f2.u(), crossVT) * d ;
        
        return (mult44(t1, t2)) ;
    }

    Transform  view(const float near, const float far, const float angle) {
        Transform t;
        
        if ((angle > 0.0) && (near < far)) {
            float tanAngle = tan(angle * 0.5 * M_PI / 180.0);
            float cotAngle = 1.0 / tanAngle ;
            
            t.m[0][0] = cotAngle ;
            t.m[1][1] = cotAngle ;
            t.m[2][2] = ( far + near ) / ( far - near ) ;
            t.m[3][2] = 2.0 * near * far / ( far - near ) ;
            t.m[2][3] = -1.0 ;
            t.m[3][3] = 0.0 ;
        }

        return t;
    }
    
    Transform invView(const float near, const float far, const float angle) {
        Transform t;
        
        if ( ( angle > 0.0 ) && ( near < far ) ) {
            float tanAngle = tan ( angle * 0.5 * M_PI / 180.0 ) ;
            
            t.m[0][0] = tanAngle ;
            t.m[1][1] = tanAngle ;
            t.m[2][2] = 0.0 ;
            t.m[3][2] = -1.0 ;
            t.m[2][3] = ( far - near ) / ( 2.0 * near * far) ;
            t.m[3][3] = ( far + near ) / ( 2.0 * near * far) ;
        }
        return t;
    }
    
    PointF apply(const Transform& t, const PointF& p) {
        PointF pOut;
        
        for (int i = 0; i < 3; ++i) {
            float sum = 0;
            for (int j = 0; j < 3; ++j) {
                sum += p.v[j]*t.m[i][j];
            }
            
            // pw * t[i][3]. pw is always 1
            sum += t.m[i][3];
            pOut.v[i] = sum;
        }
        return pOut;
    }
   
}
}