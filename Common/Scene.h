//
//  Scene.h
//  Renderer
//
//  Created by Benjamin Gregorski on 7/15/13.
//
//

#ifndef __Renderer__Scene__
#define __Renderer__Scene__

#include <iostream>
#include <vector>

#include "BasicTypes.h"

namespace Framework {

struct Ray;
class LightSource;
class SceneObject;
    
typedef std::vector<LightSource*> LightList;
    
class Scene {
      
public :
    Scene();
    ~Scene();
    
    void setViewPoint(const PointF& viewPoint) { m_viewPoint = viewPoint; }
    
    void addLight(LightSource *);
    void addSceneObject(SceneObject *);
    
    /**
     * Trace a ray through the scene and return a color.
     */
    Color traceRay(const Ray&);
    
    /**
     * Find the object that the ray intersects first.
     */
    SceneObject* intersect(const Ray& r);
    
private:
    PointF m_viewPoint;
    
    std::vector<SceneObject*> m_scene;
    LightList m_lights;
};
    
}

#endif /* defined(__Renderer__Scene__) */
