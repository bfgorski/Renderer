//
//  Camera.m
//  Renderer
//
//  Created by Benjamin Gregorski on 11/15/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import "Camera.h"
#import "BasicTypes.h"
#import "BasicTypesImpl.h"
#import "Transform.h"

using namespace Framework;

static const float DEFAULT_FOCAL_LENGTH = 10.0f;

@implementation Camera
{
}

@synthesize posDir = m_posDir;
@synthesize focalPoint = m_focalPoint;
@synthesize up = m_up;

-(void) setDefaultFocalPoint
{
    // set focal point in front of positions along view direction.
    m_focalPoint = Math::vec3AXPlusB(self.posDir.dir, DEFAULT_FOCAL_LENGTH, self.posDir.pos);
}

-(Camera*) init
{
    [self setFov:45];
    [self setAspectRatio:(1920.0f/1080.0f)];
   
    PointF p(0,0,0);
    VectorF v; 
    v.v[0] = v.v[1] = 0;
    v.v[2] = 1;
    
    Ray r;
    r.pos = p;
    r.dir = v;
    [self setPosDir:r];
    
    [self setDefaultFocalPoint];
    return self;
}

-(Camera*) initWithRay:(Ray)r upV:(VectorF)upV Fov:(float)fov AspectRatio:(float)ar nearPlane:(float)nearPlane farPlane:(float)farPlane
{
    [self setPosDir:r];
    self.up = upV;
    [self setAspectRatio:ar];
    [self setFov:fov];
    self.nearPlane = nearPlane;
    self.farPlane = farPlane;
    [self setDefaultFocalPoint];
    return self;
}

-(void) setPos: (PointF) p
{
    m_posDir.pos = p;
}

-(PointF) getPos
{
    return self.posDir.pos;
}

-(void) setDir: (VectorF) v
{
    m_posDir.dir = v;
}

-(VectorF) getDir
{
    return self.posDir.dir;
}

-(void) setPosDir: (PointF) p Dir: (VectorF) v
{
    [self setPos:p];
    [self setDir:v];
}

- (Rectangle) getNearPlane {
    // Get a quad that describes the near plane
    PointF camPos = [self getPos] ;
    
    // determine the lower left point and the scales
    // These are half angle height and width
    float height = tan(self.fov * M_PI/360.0) * self.nearPlane ;
    float width = height * self.aspectRatio;
    
    // the center of the near plane
    // the x and y increment directions
    VectorF lookAt = (self.posDir.dir);
    Math::vec3Normalize(lookAt);
    PointF center = Math::vec3AXPlusB(lookAt, self.nearPlane, camPos);
    
    VectorF yDir = self.up;
    Math::vec3Normalize(yDir);
    
    VectorF xDir = Math::cross(lookAt, self.up);
    Math::vec3Normalize(xDir);
    
    PointF lowerLeft =  Math::vec3AMinusB(center, Math::vec3AXPlusBY(xDir, width, yDir, height));
    
    Rectangle r;
    r.bottomLeft = lowerLeft;
    r.upV = yDir;
    r.rightV = xDir;
    r.upLen = height*2;
    r.rightLen = width*2;
    return r;
}

- (void) applyTransform:(Math::Transform *)t {
    self.up = t->applyToVector(self.up);
    self.focalPoint = t->applyToPoint(self.focalPoint);
    self.posDir = t->applyToRay(self.posDir);
}







@end
