//
//  Box.h
//  Renderer
//
//  Created by Benjamin Gregorski on 10/2/13.
//
//

#ifndef __Renderer__Box__
#define __Renderer__Box__

#include <iostream>
#include "SceneObject.h"
#include "BasicTypes.h"

namespace Framework {
    
    class Box : public SceneObject {
        
    public :
        Box();
        Box(const PointF& p0, const PointF& p1);
        
        /**
         * Apply the transform to box's diagonal points
         */
        virtual void applyTransform(const Math::Transform& t);
        
        /**
         * Ray/Box intersection.
         */
        virtual SOIntersectionType intersect(const Ray& r, SOIntersection* intersectionInfo) const;
        
        /**
         * Ray/Box intersection.
         */
        virtual SOIntersectionType intersect(const Ray& r, PointF& intersectionPoint) const;

        /**
         * Create points, normals and 
         */
        virtual void createGeo(const SOCreateGeoArgs *args = nullptr) override;
        
    private:
        // Define a Box by its major diagonal
        PointF m_diagStart;
        PointF m_diagEnd;
        
    };
}

#endif /* defined(__Renderer__Box__) */
