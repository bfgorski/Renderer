//
//  IlluminateResult.h
//  Renderer
//
//  Created by Benjamin Gregorski on 7/23/13.
//
//

#ifndef __Renderer__IlluminateResult__
#define __Renderer__IlluminateResult__

#include <iostream>
#include "BasicTypes.h"

namespace Framework {
    
/**
 * Store the result of a point being illuminated by a lightsource.
 */
class IlluminateResult {
    
public :
    IlluminateResult() {}
    ~IlluminateResult() {};
    
    const Color& getDif() const { return m_diffuse; }
    const Color& getSpec() const { return m_specular; }
    const Color& getAmbient() const { return m_ambient; }
    
    void setDiffuse(const Color& c) { m_diffuse = c; }
    void setSpec(const Color& c) { m_specular = c; }
    void setAmbient(const Color& c) { m_ambient = c; }
private :
    Color m_ambient;
    Color m_diffuse;
    Color m_specular;
};
    
}

#endif /* defined(__Renderer__IlluminateResult__) */
