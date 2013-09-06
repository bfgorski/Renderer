//
//  PointLightSource.h
//  Renderer
//
//  Created by Benjamin Gregorski on 7/25/13.
//
//

#ifndef __Renderer__PointLightSource__
#define __Renderer__PointLightSource__

#include <iostream>
#include "LightSource.h"

namespace Framework {
    
/**
 * Implements a Point Light.
 */
class PointLightSource : public LightSource {
    
public:
    PointLightSource() : LightSource() {}
    PointLightSource(const PointF& pos, const Color& a, const Color& d, const Color& s, const float i, const char * name = "Point Light");
    ~PointLightSource() {}
    PointLightSource(const PointLightSource& p) : LightSource(p) {}
    PointLightSource& operator=(PointLightSource&);
    
    virtual bool illuminate(const PointF& p, const VectorF& n, const PointF& eye, const float pToLVisibility, const SceneObject* obj, IlluminateResult& r) const;
    
private:
    
};
    
}

#endif /* defined(__Renderer__PointLightSource__) */
