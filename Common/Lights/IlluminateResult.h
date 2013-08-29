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
    
    void setDiffuse(const Color& c) { m_diffuse = c; }
    
private :
    Color m_ambient;
    Color m_diffuse;
    Color m_specular;
    
    void * m_data;
};
    
}

#endif /* defined(__Renderer__IlluminateResult__) */
