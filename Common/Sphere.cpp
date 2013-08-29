//
//  Sphere.cpp
//  Renderer
//
//  Created by Benjamin Gregorski on 6/23/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Sphere.h"
#include "BasicTypesImpl.h"

using namespace Framework;

Sphere::Sphere() : m_radius(1.0)
{
    m_pos.v[0] = m_pos.v[1] = m_pos.v[2] = 0;
}

Sphere::Sphere(const float r, const vec3& pos) : m_radius(r), m_pos(pos) {}

Sphere::Sphere(const Sphere& s) : m_radius(s.m_radius), m_pos(s.m_pos)
{
}

Sphere& Sphere::operator=(const Framework::Sphere &s)
{
    if (this == &s) {
        return (*this);
    }
    m_radius = s.m_radius;
    m_pos = s.m_pos;
    return (*this);
}
                          

Sphere::~Sphere()
{
}

SOIntersectionType Sphere::intersect(const Ray& r, SOIntersection *intersectionInfo) {
    PointF rayPos = r.pos;
    
    // if the ray starts inside the sphere move it outside
    //int inside = 0 ;
    /*if (contains(ray_position)) {
        ray_position -= 2 * _radius * r.direction() ;
        inside = 1 ;
    }*/
    vec3 v = Math::vec3AMinusB(center(), rayPos) ;
    float d = Math::dot3(r.dir,v) ;
    
    if (d <= 0) {
        return SOIntersectionNone;
    }
    
    float length = Math::vec3Len(v);
    float angle = asin(d/length);
    float distance = cos(angle)*length ;
    
    if (distance > getRadius()) {
        return SOIntersectionNone;
    }
    
    float rayLength = sqrt(length*length - distance*distance) ;
    float offsetLength = sqrt(getRadius()*getRadius() - distance * distance) ;
    
    // determine which intersection point if any to take
    PointF nearInt = Math::vec3AXPlusB(r.getDir(), (rayLength - offsetLength), r.getPos());
    //ray_position + r.direction() * (ray_length - offset_length) ;
    
    // first check to see if the near intesection is not behind the ray
    // this requires that we use the ray's original position
    if (Math::dot3(Math::vec3AMinusB(nearInt,r.pos), r.dir) >= 0) {
        if (NULL != intersectionInfo) {
            intersectionInfo->setPoint(nearInt);
            
            VectorF n = Math::vec3AMinusB(nearInt, center());
            Math::vec3Normalize(n);
            intersectionInfo->setNormal(n);
            intersectionInfo->setType(SOIntersectionEntering);
        }
        // Check to see if texture coordinates need to be generated
        /*if ( material().tex2D() ) {
            float phi = acos( (i.z() - center().z())/radius() ) ;
            float r = sqrt((i.x()*i.x() + i.y()*i.y())) ;
            float theta = acos( i.x()/r ) ;
            if ( i.y() < 0 ) {
                theta = 2*M_PI - theta ;
            }
            theta = theta/M_PI*0.5 ;
            phi = phi / M_PI ;
            _mat->evaluate(phi, theta) ;
        }*/
        return (SOIntersectionEntering) ;
    }
    
    PointF farInt = Math::vec3AXPlusB(r.dir, (rayLength + offsetLength), rayPos); //ray_position + r.direction() * (ray_length + offset_length) ;

    // check to se if the far intersection is valid
    if (Math::dot3(Math::vec3AMinusB(farInt, r.pos), r.dir) >= 0) {
        if (NULL != intersectionInfo) {
            intersectionInfo->setPoint(farInt);
            
            VectorF n = Math::vec3AMinusB(farInt, center());

            // flip the normal if the ray originates inside the sphere
            //if ( inside ) { n = -n ; }

            Math::vec3Normalize(n);
            intersectionInfo->setNormal(n);
            intersectionInfo->setType(SOIntersectionLeaving);
        }
        // flip the normal if the ray originates inside the sphere
        /*if ( inside ) { n = -n ; }
        if ( material().tex2D() ) {
            float phi = acos( (i.z() - center().z())/radius() ) ;
            float r = sqrt((i.x()*i.x() + i.y()*i.y())) ;
            float theta = acos( i.x()/r ) ;
            if ( i.y() < 0 ) {
                theta = 2*M_PI - theta ;
            }
            theta = theta/M_PI*0.5 ;
            phi = phi / M_PI ;
            _mat->evaluate(phi, theta) ;
        }*/
        return (SOIntersectionLeaving) ;
    }
    return (SOIntersectionNone) ;
}

bool Sphere::intersect(const Ray& r, PointF& intersectionPoint) {
    PointF rayPos = r.pos;
    
    // if the ray starts inside the sphere move it outside
    //int inside = 0 ;
    /*if (contains(ray_position)) {
     ray_position -= 2 * _radius * r.direction() ;
     inside = 1 ;
     }*/
    vec3 v = Math::vec3AMinusB(center(), rayPos) ;
    float d = Math::dot3(r.dir,v) ;
    
    if (d <= 0) {
        return false;
    }
    
    float length = Math::vec3Len(v);
    float angle = asin(d/length);
    float distance = cos(angle)*length ;
    if (distance > getRadius()) {
        return false;
    }
    
    float rayLength = sqrt(length*length - distance*distance) ;
    float offsetLength = sqrt(getRadius()*getRadius() - distance * distance) ;
    
    // determine which intersection point if any to take
    PointF nearInt = Math::vec3AXPlusB(r.getDir(), (rayLength - offsetLength), r.getPos());
    
    // first check to see if the near intesection is not behind the ray
    // this requires that we use the ray's original position
    if (Math::dot3(Math::vec3AMinusB(nearInt,r.pos), r.dir) >= 0) {
        intersectionPoint = nearInt;
        return true;
    }
    
    PointF farInt = Math::vec3AXPlusB(r.dir, (rayLength + offsetLength), rayPos);
    
    // check to se if the far intersection is valid
    if (Math::dot3(Math::vec3AMinusB(farInt, r.pos), r.dir) >= 0) {
        intersectionPoint = farInt;
        return true;
    }
    return false;
}
























