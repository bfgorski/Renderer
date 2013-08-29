//
//  Scene.cpp
//  Renderer
//
//  Created by Benjamin Gregorski on 7/15/13.
//
//

#include "Scene.h"
#include "SceneObject.h"
#include "LightSource.h"
#include "BasicTypesImpl.h"

namespace Framework {
    
Scene::Scene() :m_scene(10) {

}

Scene::~Scene() {
    
}

void Scene::addLight(LightSource * l) {
    m_lights.push_back(l);
}

void Scene::addSceneObject(SceneObject *so) {
    m_scene.push_back(so);
}

Color Scene::traceRay(const Framework::Ray& r) {
    SceneObject *closestObject = intersect(r);
    
    if (NULL == closestObject) {
        return Color(0,0,0);
    }
    
    Color c;
    
    SOIntersection intersection;
    SOIntersectionType intersectionType = closestObject->intersect(r, &intersection);
    
    if (SOIntersectionNone == intersectionType) {
        return Color(0,0,0);
    }
    
    // Accumulate Color from lights
    for(LightList::const_iterator it = m_lights.begin(); it != m_lights.end(); ++it) {
        IlluminateResult r;
        LightSource *l = (*it);
        float visibility = 1.0f; // TODO trace shadow ray
        
        bool illumResult = l->illuminate(intersection.getPoint(), intersection.getNormal(), m_viewPoint, visibility, closestObject, r);
        
        if (!illumResult) {
            continue;
        }
        
        c.accumulateColor(r.getDif());
    }
    
    return c;
}
    
SceneObject *Scene::intersect(const Ray& r) {
    SceneObject *closestObject = NULL;
    float closestDistance = 1e6;
    
    for (int i = 0; i < m_scene.size(); ++i) {
        SceneObject *s = m_scene[i];
        PointF intersectionPoint;
        bool intersectsObject = s->intersect(r, intersectionPoint);
        if (intersectsObject) {
            float dist = Math::vec3FastDist(r.pos, intersectionPoint);
            
            if (dist < closestDistance) {
                closestDistance = dist;
                closestObject = s;
            }
        }
    }
    return closestObject;
}
    
}