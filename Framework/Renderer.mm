//
//  Renderer.m
//  Renderer
//
//  Created by Benjamin Gregorski on 11/14/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import "Renderer.h"
#include "SceneObject.h"
#import "Camera.h"
#import "FrameBuffer.h"

using namespace Framework;

@implementation Renderer
{
    Camera * m_cam;
    FrameBuffer * m_fb;
}

@synthesize name;

-(void) init: (NSString*) n
{
    m_name  = n;
    SceneObject * so = new SceneObject("hello");
    m_so = so;
    m_cam = [Camera alloc];
    [m_cam init];
    
    m_fb = [FrameBuffer alloc];
    [m_fb init:1024 height:768];
}

-(void) render: (NSString**) options
{
    NSLog(@"Rendering");
    
    SceneObject * so = (SceneObject*)m_so;
    NSLog(@"Object %s", so->getName());
}

-(void) parseOptions
{
    
}

+(int) numInstances
{
    return 1;
}

-(void) runUnitTests
{
    
}
@end
