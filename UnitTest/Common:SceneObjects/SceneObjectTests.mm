//
//  SceneObjectTests.m
//  Renderer
//
//  Created by Benjamin Gregorski on 7/21/13.
//
//

#import "SceneObjectTests.h"

#include "BasicTypesImpl.h"
#include "SOIntersection.h"
#include "Sphere.h"
#include "PointLightSource.h"

using namespace Framework;

@implementation SceneObjectTests
{
}

- (void)testSphere {
    vec3 pos(0,0,0);
    Sphere * so = new Sphere(1.0f, pos);
    
    PointF rayPos(0,10,10);
    VectorF dir(0,-1,-1);
    Math::vec3Normalize(dir);
    Ray r(rayPos, dir);
    
    SOIntersection i;
    SOIntersectionType t = so->intersect(r, &i);
    
    STAssertEquals(SOIntersectionEntering, t, @"Wrong Intersection Type");
}

- (void)testPlane {
    // test plane intersection
}

- (void)testPointLight {
    // Sphere at 0,0,0
    // Point Light at 0,1,0
    vec3 pos(0,0,0);
    Sphere * so = new Sphere(1.0f, pos);
    
    /*PointF rayPos(0,10,10);
    VectorF dir(0,-1,-1);
    Math::vec3Normalize(dir);
    Ray r(rayPos, dir);*/
    
    //SOIntersection i;
    //SOIntersectionType t = so->intersect(r, &i);

    PointF lightPos(0,10,10);
    Color diffuseColor(1,0,01);
    
    PointLightSource pl;
    pl.setPos(lightPos);
    pl.setDif(diffuseColor);
    pl.setIntensity(1);
    
    PointF testPoint(0,1,0);
    VectorF normal(0,1,0);
    PointF eye(0,10,10);
    Framework::IlluminateResult r;
    bool b = pl.illuminate(testPoint, normal, eye, 1.0f, so, r);
    
    STAssertEquals(true, b, @"Bad Lighting Calculation");
}

- 

@end
