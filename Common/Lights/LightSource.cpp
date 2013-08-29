//
//  LightSource.cpp
//  Renderer
//
//  Created by Benjamin Gregorski on 7/23/13.
//
//

#include "LightSource.h"

namespace Framework {
    
LightSource::LightSource() : SceneObject(), m_ambient(), m_diffuse(), m_specular(), m_intensity(0) {
    m_fallOff[0] = m_fallOff[1] = m_fallOff[2] = 0.0f;
}
    
LightSource::LightSource(const LightSource& l) :
    m_ambient(l.m_ambient),
    m_diffuse(l.m_diffuse),
    m_specular(l.m_specular),
    m_intensity(l.m_intensity)
{
    m_fallOff[0] = l.m_fallOff[0];
    m_fallOff[1] = l.m_fallOff[1];
    m_fallOff[2] = l.m_fallOff[2];
}
    
LightSource::LightSource(const Color& a, const Color& d, const Color& s, const float i) :
    m_ambient(a),
    m_diffuse(d),
    m_specular(s),
    m_intensity(i)
{
    m_fallOff[0] = 0;
    m_fallOff[1] = 0;
    m_fallOff[2] = 0.1f;
}
    
LightSource& LightSource::operator=(const Framework::LightSource & l) {
    if (this == &l) {
        return (*this);
    }
    
    m_ambient = l.m_ambient;
    m_diffuse = l.m_diffuse;
    m_specular = l.m_specular;
    m_intensity = l.m_intensity;    
    m_fallOff[0] = l.m_fallOff[0];
    m_fallOff[1] = l.m_fallOff[1];
    m_fallOff[2] = l.m_fallOff[2];

    return (*this);
}

}