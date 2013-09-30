//
//  Camera.h
//  Renderer
//
//  Created by Benjamin Gregorski on 11/15/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BasicTypes.h"
#import "Rectangle.h"
#import "Transform.h"

using namespace Framework;

@interface Camera : NSObject
{
}

// Near clipping plane distance from camera point.
@property(readwrite, assign) float nearPlane;

// Far clipping plane used for calculating a projection matrix
@property(readwrite, assign) float farPlane;

// Field of view in degrees
@property(readwrite, assign) float fov;

// Aspect ratio of camera sceen with/height
@property(readwrite, assign) float aspectRatio;

// Position and look at direction
@property(readwrite, assign) Ray posDir;

// The up direction for the camera
@property(readwrite, assign) VectorF up;

// Focal point
@property(readwrite, assign) PointF focalPoint;

-(Camera*) init;

/**
 * Init camera with position, direction, up vector, field of view, aspect ratio and near plane.
 *
 */
-(Camera*) initWithRay:(Ray) r upV:(VectorF)upV Fov:(float) fov AspectRatio:(float) ar nearPlane:(float)nearPlane farPlane:(float)farPlane;

-(void) setPos: (PointF) p;
-(PointF) getPos;

-(void) setDir: (VectorF) v;
-(VectorF) getDir;

-(void) setPosDir: (PointF) p Dir: (VectorF) v;

/**
 * Return a Quad that describes the near plane.
 */
-(Rectangle) getNearPlane;

/**
 * Apply a 4x4 transformation to
 */
-(void) applyTransform:(Math::Transform*)t;
@end
