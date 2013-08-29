//
//  SOIntersection.h
//  Renderer
//
//  Created by Benjamin Gregorski on 7/16/13.
//
//

#ifndef __Renderer__SOIntersection__
#define __Renderer__SOIntersection__

#include <iostream>
#include "BasicTypes.h"

class SceneObject;

enum SOIntersectionType {
    SOIntersectionNone = 0,
    SOIntersectionEntering = 1,
    SOIntersectionLeaving
};

namespace Framework {
    class SOIntersection {
        
    public:
        SOIntersection() : m_so(NULL), m_intersection(), m_normal(), m_type(SOIntersectionNone){};
        ~SOIntersection() {};
        //SOIntersection(const SOIntersection&);
        //SOIntersection& operator=(const SOIntersection&);
        
        void setObject(SceneObject *so) { m_so = so; }
        void setPoint(const PointF& p) { m_intersection = p; }
        void setNormal(const VectorF& v) { m_normal = v; }
        void setType(const SOIntersectionType t) { m_type = t; }
        void set(SceneObject *so, const PointF& i, const VectorF& n, SOIntersectionType type);
        
        const SceneObject * getObject() const { return m_so; }
        const PointF& getPoint() const { return m_intersection; }
        const VectorF& getNormal() const { return m_normal; }
        SOIntersectionType getType() const { return m_type; }
        
    private:
        SceneObject * m_so;
        PointF m_intersection;
        VectorF m_normal;
        SOIntersectionType m_type;
    };
}

#endif /* defined(__Renderer__SOIntersection__) */
