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
class SOIntersection;
    
class Scene {

public:
    
    /**
     * Iterate over all SceneObjects.
     *
     *  SceneIterator it(scene);
        for( SceneIterator it(scene); it.current(); it.next()) {
            SceneObject *so = it.current();
        }
     
        SceneObject *so;
        while(so = it.current()) {
     
            it.next();
        }
     */
    class Iterator {
      
    public:
        Iterator(Scene* s);
        ~Iterator();
        
        Iterator& operator=(const Iterator&);
        
        Iterator& operator++();
        Iterator& next();
        
        SceneObject* operator*();
        SceneObject* current();
        
        void reset();
        
    private:
        Scene * m_scene;
        unsigned int m_index;
    };
    
    
public :
    Scene();
    ~Scene();
    
    void setViewPoint(const PointF& viewPoint) { m_viewPoint = viewPoint; }
    
    void addLight(LightSource *);
    void addSceneObject(SceneObject *);
    
    /**
     * Trace a ray through the scene and return a color.
     */
    Color traceRay(const Ray& r) const;
    
    /**
     * Trace a shadow ray from the given point to the indicated light source.
     *
     * @return The fraction of the light visible from the ray's position.
     */
    float traceShadowRay(const PointF& p, const LightSource& l) const;
    
    /**
     * Find the object that the ray intersects first.
     * and recursively trace until the indicated depth is met.
     * 
     * @param intersectionInfo  Store intersected object and intersection point.
     * @param depth
     *
     * @return Pointer to the closest object or NULL
     */
    SceneObject* intersect(const Ray& r, SOIntersection* intersectionInfo = NULL, const unsigned int depth = 0) const;
    
private:
    typedef std::vector<SceneObject*> SceneObjectList;
    typedef std::vector<LightSource*> LightList;

    PointF m_viewPoint;
    
    SceneObjectList m_scene;
    LightList m_lights;
};
    
}

#endif /* defined(__Renderer__Scene__) */
