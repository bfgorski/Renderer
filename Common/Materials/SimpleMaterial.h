//
//  SimpleMaterial.h
//  Renderer
//
//  Created by Benjamin Gregorski on 9/15/13.
//
//

#ifndef __Renderer__SimpleMaterial__
#define __Renderer__SimpleMaterial__

#include <iostream>
#include "Material.h"

namespace Framework {
  
/**
 * The SimpleMaterial class models a material
 * with constant diffuse, specular and ambient colors.
 */
class SimpleMaterial : public Material {
    
public :
    SimpleMaterial(const Color& d, const Color& s, const float specExp, const Color& a);
    ~SimpleMaterial() {};
   
    virtual bool evaluate(const MaterialParams& matParams, MaterialInfo& materialInfo) const;
    
private:
    Color m_diffuse;
    Color m_specular;
    float m_specExp;
    Color m_ambient;
};

}

#endif /* defined(__Renderer__SimpleMaterial__) */
