//
//  LightSource.h
//  Renderer
//
//  Created by Benjamin Gregorski on 7/23/13.
//
//

#ifndef __Renderer__LightSource__
#define __Renderer__LightSource__

#include <iostream>
#include "SceneObject.h"
#include "IlluminateResult.h"

namespace Framework {

/**
 * Implements Base Class functionality for lights.
 */
class LightSource : public SceneObject {

public:
    
    LightSource();
    ~LightSource(){};
    LightSource(const LightSource& );
    LightSource(const Color& a, const Color& d, const Color& s, const float i);
    LightSource& operator=(const LightSource&);
    
    void setAmb(const Color& c) { m_ambient = c; }
    void setDif(const Color& c) { m_diffuse = c; }
    void setSpec(const Color& c) { m_specular = c; }
    void setIntensity(const float f) { m_intensity = f; }
    
    const Color& getAmb() const { return m_ambient; }
    const Color& getDif() const { return m_diffuse; }
    const Color& getSpec() const { return m_specular; }
    float getIntensity() const { return m_intensity; }
    
    /**
     * Determine if the indicated Ray "sees" the light.
     */
    virtual SOIntersectionType intersect(const Ray& r, SOIntersection* intersectionInfo) const { return SOIntersectionNone; }
    
    virtual SOIntersectionType intersect(const Ray& r, PointF& intersectionPoint) const { return SOIntersectionNone; }
    
    /**
     * Compute the intensity of the light.
     *
     * @param p     Point to illuminate
     * @param n     Normal Vector
     * @param eye   Eye Point
     * @param pToLVisibility Point to LightSource visibility 1 = no attenuation 0 = completely obscured
     * @param obj   The SceneObject being illuminated.
     * @param result    Store the result of the illumination here
     *
     * @return bool true/false indicating whether or not the result can be ignored.
     */
    virtual bool illuminate(const PointF& p, const VectorF& n, const PointF& eye, const float pToLVisibility, const SceneObject* obj, IlluminateResult& result) const = 0;
private:
    
    Color m_ambient;
    Color m_diffuse;
    Color m_specular;
    
    float m_intensity;
    
    /** 
     * Ax^3 + Bx^2 + Cx intensity falloff over distance
     * other lights may implement different falloff functions.
     */
    float m_fallOff[3];
};

}

#endif /* defined(__Renderer__LightSource__) */
