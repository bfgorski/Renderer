//
//  Material.cpp
//  Renderer
//
//  Created by Benjamin Gregorski on 9/5/13.
//
//

#include "Material.h"

using namespace Framework;

MaterialParams::MaterialParams()
: m_point(), m_texCoord(), m_normal(), m_tangent(), m_biTangent()
{
}

MaterialParams::MaterialParams(
    const PointF& p,
    const TexCoord4& tex,
    const Normal& n,
    const Tangent& t,
    const Tangent& biT
)
: m_point(p), m_texCoord(tex), m_normal(n), m_tangent(t), m_biTangent(biT)
{
}

MaterialInfo::MaterialInfo()
: m_normal(), m_diffuse(0.5,0.5,0.5,1), m_specular(1,1,1,1), m_specExp(), m_ambient()
{
    m_specExp.v[0] = 50;
}

Material::Material() : m_needsNormal(false), m_needsCoordinateFrame(false), m_needsTexCoord(false)
{
}