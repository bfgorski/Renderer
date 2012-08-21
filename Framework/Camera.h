//
//  Camera.h
//  Renderer
//
//  Created by Benjamin Gregorski on 11/15/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BasicTypes.h"

@interface Camera : NSObject
{
}

@property(readwrite, assign) float fov, aspectRatio, width, height;

@property(readwrite, assign) Ray posDir;
@property(readwrite, assign) PointF focalPoint;

-(Camera*) init;
-(Camera*) init: (Ray) r Fov: (float) fov AspectRatio: (float) ar;

-(void) setPos: (PointF) p;
-(PointF) getPos;

-(void) setDir: (VectorF) v;
-(VectorF) getDir;

-(void) setPosDir: (PointF) p Dir: (VectorF) v;

@end
