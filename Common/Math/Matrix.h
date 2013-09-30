//
//  Matrix.h
//  Renderer
//
//  Created by Benjamin Gregorski on 9/17/13.
//
//

#ifndef Renderer_Matrix_h
#define Renderer_Matrix_h

#include "BasicTypes.h"

namespace Framework { namespace Math {
    
    /**
     * 4x4 matrix
     */
    struct Matrix44 {
    public:
        // Row major order
        float m[4][4];
        
        /**
         * Default constructor creates an identity matrix.
         */
        Matrix44();
        
        float get(const int row, const int col) const { return m[row][col]; }
        void set(const int row, const int col, const float f) { m[row][col] = f; }
        
        /**
         * Set to the 0 matrix
         */
        void zero();
        
        /**
         * Set to identity matrix.
         */
        void identity();
        
        /**
         * Scale all elements by f.
         */
        void scale(const float f);
        
        /**
         * Apply the Transform to the indicated Point in homogeneous coordinates with w = 1.
         * Transform is applied as:
         *
         *  [px,py,pz,1] * M
         *
         * @param p 3D point with W set to 1
         *
         * @return  PointF
         */
        PointF applyToPoint(const PointF& p) const;
        
        /**
         * Apply the Transform to the indicated Vector in homogeneous coordinates with w = 0.
         * Transform is applied as:
         *
         *  [vx,vy,vz,0] * M
         *
         * @param v 3D point with W set to 1
         *
         * @return  VectorF
         */
        VectorF applyToVector(const VectorF& v) const;
        
        /**
         * Apply the Transform to the Ray's position and direction.
         */
        Ray applyToRay(const Ray& r) const;
        
    };
    
    typedef struct Matrix44 Matrix44;
    /**
     * Return m1*m2.
     */
    Matrix44 mult44(const Matrix44& m1, const Matrix44& m2);
    Matrix44 scale44(const Matrix44& m, const float f);
}
    
}

#endif
