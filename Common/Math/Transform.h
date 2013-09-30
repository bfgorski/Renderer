//
//  Transform.h
//  Renderer
//
//  Created by Benjamin Gregorski on 9/17/13.
//
//  Methods for creating 4x4 transforms for modeling and view matrices.
//  The matrices are setup as:
//      v * M = v'
//

#ifndef Renderer_Transform_h
#define Renderer_Transform_h

#include "Matrix.h"

namespace Framework { namespace Math {
    
typedef Matrix44 Transform;

/**
 * Create a 4x4 matrix to translate by the given vector.
 * The translation is in the last row.
 *
 * @param   X,Y,Z vector.
 * @return Transform
 */
Transform translateBy(const VectorF& v);
Transform translateBy(const float x, const float y, const float z);

/**
 * Create transforms to rotate about the X, Y, or Z-axis K degrees.
 */
Transform rotateX(const float angle, const AngleType = DEGREES);
Transform rotateY(const float angle, const AngleType = DEGREES);
Transform rotateZ(const float angle, const AngleType = DEGREES);
    
/**
 * Rotatation matrix about the given vector.
 */
//Transform rotateV(const VectorF& v, const float angle, const AngleType = DEGREES);
  
/**
 * Transform from one coordinate frame to another.
 *
 * @param from  The current Frame
 * @param to    The new coordinate Frame.
 */
Transform frameToFrame(const Frame& from, const Frame& to);
    
/**
 * Viewing matrix given near, far and view angle
 *
 * @param angle View frustum angle in degrees
 */
Transform view(const float near, const float far, const float angle);
    
/**
 * Inverse viewing matrix.
 */
Transform invView(const float near, const float far, const float angle);
    
/**
 * Apply the Transform to the indicated Point in homogeneous coordinates with w = 1.
 * Transform is applied as:
 *
 *  [px,py,pz,1] * T
 *
 * @param t 4x4 Transform
 * @param p 3D point with W set to 1
 *
 * @return  PointF
 */
PointF apply(const Transform& t, const PointF& p);
    
/**
 * Apply the Transform to the indicated Point in homogeneous coordinates with w = 0.
 * Transform is applied as:
 *
 *  [vx,vy,vz,0] * T
 *
 * @param t 4x4 Transform
 * @param v 3D Vector
 *
 * @return  VectorF
 */
VectorF apply(const Transform& t, const VectorF& v);
    
}
}

#endif
