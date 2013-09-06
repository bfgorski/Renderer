//
//  SceneObject.h
//  Renderer
//
//  Created by Benjamin Gregorski on 11/14/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef Renderer_SceneObject_h
#define Renderer_SceneObject_h

#include <string>
#include "SOIntersection.h"

namespace Framework {
    
class SceneObject {
    
public:
    SceneObject();
    virtual ~SceneObject();
    SceneObject(const SceneObject&);
    SceneObject(const char * name);
    
    SceneObject& operator=(const SceneObject&);
    
    void setName(const char * s) { m_name = s; }
    void setName(const std::string& s) { m_name = s; }
    
    /**
     * Position in 3-space.
     */
    void setPos(const PointF& p) { m_pos = p; }
    
    const std::string& getName() const { return m_name; }
    const PointF& getPos() const { return m_pos; }
    
    /**
     * Determine if the indicated Ray intersects the object.
     */
    virtual SOIntersectionType intersect(const Ray& r, SOIntersection* intersectionInfo) const = 0;
    
    /**
     * Determine if the indicated Ray intersects the object
     * and get the intersection point only.
     *
     * This is intended to be a fast check for intersection.
     */
    virtual SOIntersectionType intersect(const Ray& r, PointF& intersectionPoint) const = 0;
    
protected:
    std::string m_name;
    PointF m_pos;
};
    
}
#endif
