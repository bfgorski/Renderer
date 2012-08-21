//
//  SceneObject.h
//  Renderer
//
//  Created by Benjamin Gregorski on 11/14/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef Renderer_SceneObject_h
#define Renderer_SceneObject_h

#include "BasicTypes.h"
   
namespace Framework {
    
class SceneObject {
    
public:
    SceneObject(const char * name);
    
    const char * getName() const { return m_name; }
    const int getType() const { return 1; }
    
protected:
    const char * m_name;
};
    
}
#endif
