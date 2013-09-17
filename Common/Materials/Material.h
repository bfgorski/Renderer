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
 * Parameters for evaluating a material.  
 */
class MaterialParams {
    
public:
    MaterialParams();
    MaterialParams(
        const PointF& p,
        const TexCoord4& tex,
        const Normal& n = VZero,
        const Tangent& t = VZero,
        const Tangent& biT = VZero
    );
    
    const PointF& getPoint() const { return m_point; }
    const TexCoord4& getTexCoord() const { return m_texCoord; }
    const Normal& getNormal() const { return m_normal; }
    const Tangent& getTangent() const { return m_tangent; }
    const Tangent& getBiTangent() const { return m_biTangent; }
    
private:
    PointF m_point;
    TexCoord4 m_texCoord;
    Normal m_normal;
    Tangent m_tangent;
    Tangent m_biTangent;
};

/**
 * Data returned by material evaluation used for lighting.
 */
class MaterialInfo {
    
public:
    MaterialInfo();
   
    const Normal& getNormal() const { return m_normal; }
    const Color& getDiffuse() const { return m_diffuse; }
    const Color& getSpecular() const { return m_specular; }
    const Color& getAmbient() const { return m_ambient; }
    const float getSpecExp() const { return m_specExp.v[0]; }
    
    void setNormal(const Normal& n) { m_normal = n; }
    void setDiffuse(const Color& c) { m_diffuse = c; }
    void setSpeclar(const Color& c) { m_specular = c; }
    void setSpecExp(const float f) { m_specExp.v[0] = f; }
    void setAmbient(const Color& c) { m_ambient = c; }
    
private:
    Normal m_normal;
    Color m_diffuse;
    Color m_specular;
    
    /**
     * 4 channel specular falloff
     */
    vec4 m_specExp;
    Color m_ambient;
};

/**
 * Calculates material properties for an object.
 */
class Material {
  
public :
    Material();
    ~Material() {};
    
    /**
     * Materials can indicate which parameters they need.
     * e.g. a simple color material does not need the surface normal or
     *      the tangent and bitangent of the coordinate frame.
     */
    bool needsNormal() const { return m_needsNormal; }
    bool needsCoordinateFrame() const { return m_needsCoordinateFrame; }
    bool needsTexCoord() const { return m_needsTexCoord; }
    
    /**
     * Evaluate the material using the given params and return the information
     * in the given MaterialInfo object.
     */
    virtual bool evaluate(const MaterialParams& matParams, MaterialInfo& materialInfo) const = 0;
    
protected:
    bool m_needsNormal;
    bool m_needsCoordinateFrame;
    bool m_needsTexCoord;
    
private:
    
};

}
#endif /* defined(__Renderer__Material__) */
