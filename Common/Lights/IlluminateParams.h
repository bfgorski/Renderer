//
//  IlluminateParams.h
//  Renderer
//
//  Created by Benjamin Gregorski on 9/16/13.
//
//

#ifndef __Renderer__IlluminateParams__
#define __Renderer__IlluminateParams__

#include <iostream>
#include "BasicTypes.h"

namespace Framework {
    
    /**
     * IlluminateParams store data needed by a light to calculate
     * the lighting intensity for a point in space.
     */
    class IlluminateParams {
        
    public :
        /**
         * Construct a new set of illumination parameters.
         * 
         * @param specParams specular highlight parameters from object's Material.
         */
        IlluminateParams(
            const PointF& p,
            const Normal& n,
            const PointF& eye,
            const float specExp,
            const float visibility,
            const Tangent& t = VZero,
            const Tangent& biT = VZero
        );
        
        void setPoint(const PointF& p) { m_point = p; }
        void setNormal(const Normal& n) { m_normal = n; }
        void setEyePoint(const PointF& p) { m_eye = p; }
        void setSpecExp(const float f) { m_specular.v[0] = f; }
        void setVisibility(const float v) { m_visibility = v; }
        void setTangent(const Tangent& t) { m_tangent = t; }
        void setBiTangent(const Tangent& t) { m_biTangent = t; }
        
        const PointF& getPoint() const { return m_point; }
        const Normal& getNormal() const { return m_normal; }
        const PointF& getEyePoint() const { return m_eye; }
        float getSpecExp() const { return m_specular.v[0]; }
        float getVisibility() const { return m_visibility; }
        const Tangent& getTangent() const { return m_tangent; }
        const Tangent& getBiTangent() const { return m_biTangent; }
        
    private:
        PointF m_point;
        Normal m_normal;
        PointF m_eye;
        vec4 m_specular;
        float m_visibility;
        Tangent m_tangent;
        Tangent m_biTangent;
    };
}
#endif /* defined(__Renderer__IlluminateParams__) */
