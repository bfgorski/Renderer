//
//  Matrix.c
//  Renderer
//
//  Created by Benjamin Gregorski on 9/17/13.
//
//

#include <stdio.h>
#include <string.h>
#include "Matrix.h"

namespace Framework { namespace Math {
   
Matrix44::Matrix44() {
    identity();
}

void Matrix44::zero() {
    memset(m, 0, sizeof(vec4)*4);
}
    
void Matrix44::identity() {
    memset(m, 0, sizeof(vec4)*4);
    set(0,0,1);
    set(1,1,1);
    set(2,2,1);
    set(3,3,1);
}
    
void Matrix44::scale(const float f) {
    for (int i = 0 ; i < 4 ; i++) {
        for (int j = 0 ; j < 4 ; j++) {
            set(i, j, (get(i,j)*f));
        }
    }
}
    
PointF Matrix44::applyToPoint(const PointF &p) const {
    PointF pOut;
    
    for (int i = 0; i < 3; ++i) {
        float sum = 0;
        for (int j = 0; j < 3; ++j) {
            sum += p.v[j]*m[i][j];
        }
        
        // pw * t[i][3]. pw is always 1
        sum += m[i][3];
        pOut.v[i] = sum;
    }
    return pOut;
}
    
VectorF Matrix44::applyToVector(const VectorF &v) const {
    VectorF pOut;
    
    for (int i = 0; i < 3; ++i) {
        float sum = 0;
        for (int j = 0; j < 3; ++j) {
            sum += v.v[j]*m[i][j];
        }
        
        pOut.v[i] = sum;
    }
    return pOut;
}

Ray Matrix44::applyToRay(const Ray &r) const {
    PointF p = applyToPoint(r.getPos());
    VectorF v = applyToPoint(r.getDir());
    return Ray(p,v);
}
    
Matrix44 mult44(const Matrix44& m1, const Matrix44& m2) {
    Matrix44 m;
    float sum;
    
    for (int i = 0 ; i < 4 ; i++) {
        for (int j = 0 ; j < 4 ; j++) {
            
            sum = 0.0 ;
            // Row i from m1 times Col j from m2
            for (int k = 0 ; k < 4 ; k++ ) {
                sum += m1.get(i,k) * m2.get(k,j);
            }
            
            m.set(i,j,sum);
        }
    }
    
    return m;
}
    
Matrix44 scale44(const Matrix44& mIn, const float f) {
    Matrix44 mOut;
    
    for (int i = 0 ; i < 4 ; i++) {
        for (int j = 0 ; j < 4 ; j++) {
            mOut.set(i, j, (mIn.get(i,j)*f));
        }
    }
    
    return mOut;
}

}
}