//
//  PointLightSource.cpp
//  Renderer
//
//  Created by Benjamin Gregorski on 7/25/13.
//
//

#include "PointLightSource.h"
#include "BasicTypesImpl.h"

namespace Framework {
    
    
PointLightSource::PointLightSource(const PointF& pos, const Color& a, const Color& d, const Color& s, const float i, const char *name)
:LightSource(a,d,s,i)
{
    setPos(pos);
    setName(name);
}
    
PointLightSource& PointLightSource::operator=(Framework::PointLightSource & p) {
    LightSource::operator=(p);
    return (*this);
}
    
bool PointLightSource::illuminate(const PointF &p, const VectorF &n, const PointF &eye, const float pToLVisibility, const Framework::SceneObject *obj, Framework::IlluminateResult &r) {
    
    // Diffuse N dot L
    vec3 L = Math::vec3AMinusB(this->getPos(), p);
    Math::vec3Normalize(L);
    float diffuseItensity = Math::max(Math::dot3(n, L), 0);
    
    Color diffuse = getDif();
    diffuse.scale(diffuseItensity*pToLVisibility);
    r.setDiffuse(diffuse);
    return true;
}
    
}