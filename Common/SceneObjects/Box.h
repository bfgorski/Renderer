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
        /**
         * Default Box is centered at the origin
         */
        Box();
        
        /**
         * Create a new box with a frame and dimensions.
         *
         * @param f Frame at the box center.
         */
        Box(const Frame& f, const float uDim, const float vDim, const float wDim);
        
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
        
        void intersectionHelper(
            const Ray& r,
            const PointF& p,
            const VectorF& v,
            PointF& closestIntersection,
            VectorF& closestNormal,
            float& closestDistance
        ) const;
        
        SOIntersectionType findIntersection(const Ray& r, PointF& closestIntersection, VectorF& closestNormal) const;
        
        void createGeoHelper(
            const PointF& faceCenter,
            const VectorF& faceNormal,
            const VectorF& v0,
            const float v0Scale,
            const VectorF& v1,
            const float v1Scale,
            float * v
        );
        
        /* 
         * Define a Box with a normalized frame and three dimensions
         * The
         */
        Frame m_frame;
        
        float m_dimensions[3];
    };
}

#endif /* defined(__Renderer__Box__) */
