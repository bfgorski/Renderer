//
//  SimpleMaterial.cpp
//  Renderer
//
//  Created by Benjamin Gregorski on 9/15/13.
//
//

#include "SimpleMaterial.h"

using namespace Framework;

SimpleMaterial::SimpleMaterial(const Color& d, const Color& s, const float specExp, const Color& a)
: m_diffuse(d), m_specular(s), m_specExp(specExp), m_ambient(a)
{
}

bool SimpleMaterial::evaluate(const Framework::MaterialParams &matParams, Framework::MaterialInfo &materialInfo) const
{
    materialInfo.setDiffuse(m_diffuse);
    materialInfo.setSpeclar(m_specular);
    materialInfo.setSpecExp(m_specExp);
    materialInfo.setAmbient(m_ambient);
    return true;
}