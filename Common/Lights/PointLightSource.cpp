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
    
bool PointLightSource::illuminate(const IlluminateParams& illuminateParams, const Framework::SceneObject *obj, Framework::IlluminateResult &r) const {
    
    // Diffuse N dot L
    vec3 L = Math::vec3AMinusB(this->getPos(), illuminateParams.getPoint());
    Math::vec3Normalize(L);
    float diffuseItensity = Math::max(Math::dot3(illuminateParams.getNormal(), L), 0);
    
    Color diffuse = getDif();
    diffuse.scale(diffuseItensity*illuminateParams.getVisibility());
    r.setDiffuse(diffuse);
    
    // Vector from surface point to view point
    VectorF viewVector = Math::vec3AMinusB(illuminateParams.getEyePoint(), illuminateParams.getPoint());
    VectorF halfAngle = Math::vec3AXPlusBY(L, 0.5f, viewVector, 0.5f);
    Math::vec3Normalize(halfAngle);
    float specIntensity = pow(Math::dot3(halfAngle, viewVector), illuminateParams.getSpecExp());
    
    Color spec = getSpec();
    spec.scale(specIntensity*illuminateParams.getVisibility());
    r.setSpec(spec);
    
    r.setAmbient(this->getAmb());
    return true;
}
    
}