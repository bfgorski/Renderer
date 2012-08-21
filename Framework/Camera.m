//
//  Camera.m
//  Renderer
//
//  Created by Benjamin Gregorski on 11/15/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import "Camera.h"
#import "BasicTypes.h"

@implementation Camera
{
    //Ray m_posDir;
}


@synthesize fov, aspectRatio, width, height, posDir=m_posDir, focalPoint=m_focalPoint;

-(void) setDefaultFocalPoint
{
    m_focalPoint.v[0] = 0;
    m_focalPoint.v[1] = 0;
    m_focalPoint.v[2] = 10;
}

-(Camera*) init
{
    [self setFov:45];
    [self setAspectRatio:1.0f];
    [self setWidth:1920];
    [self setHeight:1080];
    
    PointF p;
    p.v[0] = p.v[1] = p.v[2] = 0;
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

-(Camera*) init: (Ray) r Fov: (float) f AspectRatio: (float) ar
{
    [self setPosDir:r];
    [self setAspectRatio:ar];
    [self setFov:f];
    [self setDefaultFocalPoint];
    return self;
}

-(void) setPos: (PointF) p
{
    m_posDir.pos = p;
}

-(PointF) getPos
{
    return m_posDir.pos;
}

-(void) setDir: (VectorF) v
{
    m_posDir.dir = v;
}

-(VectorF) getDir
{
    return m_posDir.dir;
}

-(void) setPosDir: (PointF) p Dir: (VectorF) v
{
    [self setPos:p];
    [self setDir:v];
}

@end
