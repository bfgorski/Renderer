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
#include "Material.h"
#include "IlluminateParams.h"

static const float SHADOW_RAY_OFFSET = 0.001f;

namespace Framework {
    
Scene::Iterator::Iterator(Scene *s) : m_scene(s), m_index(0) {}
Scene::Iterator::~Iterator() {}
    
Scene::Iterator& Scene::Iterator::operator=(const Framework::Scene::Iterator& it) {
    if (this == &it) {
        return (*this);
    }
    
    m_scene = it.m_scene;
    m_index = it.m_index;
    
    return (*this);
}
    
SceneObject* Scene::Iterator::operator*() {
    return current();
}
    
SceneObject* Scene::Iterator::current() {
    if (m_scene->m_scene.size() >= m_index) {
        return nullptr;
    }
    return m_scene->m_scene[m_index];
}

Scene::Iterator& Scene::Iterator::operator++() {
    ++m_index;
    return (*this);
}
    
Scene::Iterator& Scene::Iterator::next() {
    ++m_index;
    return (*this);
}
    
void Scene::Iterator::reset() {
    m_index = 0;
}
    
Scene::Scene() : m_viewPoint(), m_scene(), m_lights() {}

Scene::~Scene() {
    // Delete stuff
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
    
    MaterialInfo materialInfo;
    const Material* material = closestObject->getMaterial();
    
    // Evaluate material properties
    if (NULL != material) {
        /*
         MaterialParams(
             const PointF& p,
             const TexCoord4& tex,
             const Normal& n = VZero,
             const Tangent& t = VZero,
             const Tangent& biT = VZero
         );
         */
        MaterialParams materialParams(
            intersection.getPoint(),
            intersection.getTexCoord(),
            intersection.getNormal()
        );
        
        material->evaluate(materialParams, materialInfo);
    } else {
        // Default material
        materialInfo.setNormal(intersection.getNormal());
    }
    
    /*
     const PointF& p,
     const Normal& n,
     const PointF& eye,
     const VectorF& specParams,
     const float visibility,
     const Tangent& t = VZero,
     const Tangent& biT = VZero
     
     */
    IlluminateParams illuminateParams(
        intersection.getPoint(),
        intersection.getNormal(),
        m_viewPoint,
        materialInfo.getSpecExp(),
        1.0f,
        intersection.getTangent(),
        intersection.getBiTangent()
    );
    
    Color diffuse(0,0,0,1);
    Color specular(0,0,0,1);
    Color ambient(0,0,0,1);
    
    // Accumulate Color from lights
    for(LightList::const_iterator it = m_lights.begin(); it != m_lights.end(); ++it) {
        IlluminateResult illuminateResult;
        LightSource *l = (*it);
        
        float visibility = traceShadowRay(intersection.getPoint(), (*l));
        illuminateParams.setVisibility(visibility);
        
        bool illumResult = l->illuminate(illuminateParams, closestObject, illuminateResult);
        
        if (!illumResult) {
            continue;
        }
        
        diffuse.accumulateColor(illuminateResult.getDif());
        specular.accumulateColor(illuminateResult.getSpec());
        ambient.accumulateColor(illuminateResult.getAmbient());
    }
    
    return (Math::lightSurface(diffuse, materialInfo.getDiffuse(), specular, materialInfo.getSpecular(), ambient, materialInfo.getAmbient()));
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
        
        // Use the simple intersection routine to find the intersection point only
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











