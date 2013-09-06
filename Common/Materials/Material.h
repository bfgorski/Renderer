//
//  Material.h
//  Renderer
//
//  Created by Benjamin Gregorski on 9/5/13.
//
//

#ifndef __Renderer__Material__
#define __Renderer__Material__

#include <iostream>
#include "BasicTypes.h"

namespace Framework {
    
/**
 * Parameters for evaluating a material at a point in space.
 */
class MaterialParams {
public:
    MaterialParams(const PointF&, const Normal&, const TexCoord4);
    
    const PointF& getPoint() const { return m_point; }
    
private:
    PointF m_point;
    TexCoord4 m_texCoord;
    Normal m_normal;
};

class MaterialInfo {
    
public:
    MaterialInfo();
    
private:
    Framework::Normal m_normal;
    Framework::Tangent m_tangent;
    Framework::Color m_diffuse;
    Framework::Color m_specular;
};

/**
 * Calculates material properties for an object.
 */
class Material {
  
public :
    Material();
    ~Material();
    
    /**
     * Evaluate the material at the given texture coordinate and return the information
     * in the given MaterialInfo object.
     */
    bool evaluate(const MaterialParams& matParams, MaterialInfo& materialInfo);
private:
    
};

}
#endif /* defined(__Renderer__Material__) */
