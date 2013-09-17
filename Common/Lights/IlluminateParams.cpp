//
//  IlluminateParams.cpp
//  Renderer
//
//  Created by Benjamin Gregorski on 9/16/13.
//
//

#include "IlluminateParams.h"

using namespace Framework;

IlluminateParams::IlluminateParams(
    const PointF& p,
    const Normal& n,
    const PointF& eye,
    const float specExp,
    const float visibility,
    const Tangent& t,
    const Tangent& biT)
: m_point(p), m_normal(n), m_eye(eye), m_specular(), m_visibility(visibility), m_tangent(t), m_biTangent(biT)
{
    m_specular.v[0] = specExp;
}