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
#include "SOIntersection.h"

static const float SHADOW_RAY_OFFSET = 0.001f;

namespace Framework {
    
Scene::Scene() : m_viewPoint(), m_scene(), m_lights() {

}

Scene::~Scene() {
    
}

void Scene::addLight(LightSource * l) {
    m_lights.push_back(l);
}

void Scene::addSceneObject(SceneObject *so) {
    m_scene.push_back(so);
}

Color Scene::traceRay(const Framework::Ray& r) const {
    SceneObject *closestObject = intersect(r);
    
    if (NULL == closestObject) {
        return Color(0,0,0);
    }
    
    SOIntersection intersection;
    SOIntersectionType intersectionType = closestObject->intersect(r, &intersection);
    
    if (SOIntersectionNone == intersectionType) {
        return Color(0,0,0);
    }
    
    Color c(0,0,0,1);
    
    // Accumulate Color from lights
    for(LightList::const_iterator it = m_lights.begin(); it != m_lights.end(); ++it) {
        IlluminateResult illuminateResult;
        LightSource *l = (*it);
        
        float visibility = traceShadowRay(intersection.getPoint(), (*l));
        
        bool illumResult = l->illuminate(intersection.getPoint(), intersection.getNormal(), m_viewPoint, visibility, closestObject, illuminateResult);
        
        if (!illumResult) {
            continue;
        }
        
        c.accumulateColor(illuminateResult.getDif());
    }
    
    return c;
}
    
float Scene::traceShadowRay(const Framework::PointF& p, const Framework::LightSource& l) const {
    VectorF dir = Math::vec3AMinusB(l.getPos(), p);
    float pointToLightDist = Math::vec3FastLen(dir);
    Math::vec3Normalize(dir);
    
    PointF offsetPoint = Math::vec3AXPlusB(dir, SHADOW_RAY_OFFSET, p);
    Ray r(offsetPoint, dir);
    
    SOIntersection intersectionInfo;
    SceneObject *obj = intersect(r, &intersectionInfo, 0);
    
    if (!obj) {
        return 1;
    }
    
    float pointToObjDist = Math::vec3FastDist(p, intersectionInfo.getPoint());
    return ((pointToObjDist < pointToLightDist) ? 0 : 1);
}
    
SceneObject *Scene::intersect(const Ray& r, SOIntersection* intersectionInfo, const unsigned int depth) const {
    SceneObject *closestObject = NULL;
    PointF closestPoint;
    
    float closestDistance = 1e6;
    
    for (int i = 0; i < m_scene.size(); ++i) {
        SceneObject *s = m_scene[i];
        PointF intersectionPoint;
        SOIntersectionType intersectsObject = s->intersect(r, intersectionPoint);
        if (SOIntersectionNone != intersectsObject) {
            float dist = Math::vec3FastDist(r.pos, intersectionPoint);
            
            if (dist < closestDistance) {
                closestDistance = dist;
                closestObject = s;
                closestPoint = intersectionPoint;
            }
            
            // TODO: trace reflection and refraction rays
            if (depth > 0) {
                
            }
        }
    }
    
    if (intersectionInfo && closestObject) {
        intersectionInfo->setObject(closestObject);
        intersectionInfo->setPoint(closestPoint);
    }
    
    return closestObject;
}
    
}











