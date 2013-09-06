//
//  SOIntersection.cpp
//  Renderer
//
//  Created by Benjamin Gregorski on 7/16/13.
//
//

#include "SOIntersection.h"

namespace Framework {
    void SOIntersection::set(const SceneObject *so, const PointF &i, const VectorF &n, SOIntersectionType type)  {
        m_so = so;
        m_intersection = i;
        m_normal = n;
        m_type = type;
    }
}