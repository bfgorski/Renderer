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
    
    // Early out if the surface point is not visible.
    if (illuminateParams.getVisibility() <= 0.0f) {
        return false;
    }
    
    // Diffuse N dot L
    vec3 L = Math::vec3AMinusB(this->getPos(), illuminateParams.getPoint());
    Math::vec3Normalize(L);
    float diffuseItensity = Math::max(Math::dot3(illuminateParams.getNormal(), L), 0);
    
    Color diffuse = getDif();
    diffuse.scale(diffuseItensity*illuminateParams.getVisibility());
    r.setDiffuse(diffuse);
    
    /*
     
     halfway = 0.5 * light_source - view * 0.5 ;
     halfway.normalize() ;
     temp += pow(dot( halfway, n ), m.shininess() ) * _specular * m.specular() ;
     
     */
    
    // Vector from surface point to view point
    VectorF viewVector = Math::vec3AMinusB(illuminateParams.getEyePoint(), illuminateParams.getPoint());
    Math::vec3Normalize(viewVector);
    
    VectorF halfAngle = Math::vec3AXPlusBY(L, 0.5f, viewVector, 0.5f);
    Math::vec3Normalize(halfAngle);
    
    float specBase = Math::max(0.0, Math::dot3(halfAngle, illuminateParams.getNormal()));
    float specIntensity = pow(specBase, illuminateParams.getSpecExp());
    
    Color spec = getSpec();
    spec.scale(specIntensity*illuminateParams.getVisibility());
    r.setSpec(spec);
    r.setAmbient(this->getAmb());
    
    return true;
}
    
}