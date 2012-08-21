//
//  Sphere.h
//  Renderer
//
//  Created by Benjamin Gregorski on 6/23/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Renderer_Sphere_h
#define Renderer_Sphere_h

#include "SceneObject.h"

namespace Framework {

class Sphere : public SceneObject {
    
public:
    Sphere();
    Sphere(const float r, const vec3& pos);
    Sphere(const Sphere&);
    Sphere& operator=(const Sphere&);
    virtual ~Sphere();
    
    void setRadius(const float r) { m_radius = r; }
    void setPos(const vec3& v) { 
        m_pos = v;
    }
    
    float getRadius() const { return m_radius; }
    
private:
    float m_radius;
    vec3 m_pos;
};

}
#endif
