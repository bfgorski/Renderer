//
//  Renderer.m
//  Renderer
//
//  Created by Benjamin Gregorski on 11/14/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import <ImageIO/ImageIO.h>

#import "Renderer.h"
#import "Camera.h"
#import "FrameBuffer.h"

#include "Scene.h"
#include "SceneObject.h"
#include "Sphere.h"
#include "Plane.h"
#include "BasicTypesImpl.h"
#include "PointLightSource.h"  

using namespace Framework;

@interface Renderer()

@property(strong, nonatomic) Camera* camera;
@property(strong, setter = setFrameBuffer:, getter = getFrameBuffer) FrameBuffer* frameBuffer;

@end

@implementation Renderer
{
    Scene * m_scene;
}

@synthesize name;
@synthesize frameBuffer = m_fb;
//@synthesize scene = m_scene;

-(Renderer*) init: (NSString*) n
{
    /*
     Camera (0,0,10) looking at 0,0,0
     Sphere at (0,0,0) radius 5.
     
     Light at (0,0,10)
     */
    PointF camPos(0,0,10);
    VectorF camDir(0,0,-1);
    Ray r(camPos, camDir);
    VectorF up(0,1,0);
    
    self.camera = [[Camera alloc] init:r upV:up Fov:45 AspectRatio:1.0f nearPlane:5.0f];
    self.frameBuffer = [[FrameBuffer alloc] init:100 height:100];

    m_scene = new Scene();
    self.name  = n;
    
    vec3 pos(0,0,0);
    Sphere * so = new Sphere(2.0f, pos);
    
    PointF planePos(0, 0, -20);
    VectorF planeN(0,0,1);
    Plane * plane = new Plane(planePos, planeN);
    
    Color ambient(0,0,0,1);
    Color diffuse(0.25,0.25,0.25,1);
    Color specular(0,0,0,0);
    
    PointF lightPos(5,0,5);
    PointLightSource *p0 = new PointLightSource(lightPos, ambient, diffuse, specular, 1.0f);
    m_scene->addLight(p0);
 
    Color diffuse2(0.5,0.5,0.5,1);
    PointF light2Pos(-5,0,5);
    PointLightSource* p1 = new PointLightSource(light2Pos, ambient, diffuse2, specular, 1.0f);
    m_scene->addLight(p1);
    
    m_scene->addSceneObject(so);
    m_scene->addSceneObject(plane);
    
    return self;
}

-(void) render: (NSDictionary*) options
{
    // Grab view screen from camera and cast rays
    // thrrough pixel centers.
    Rectangle viewScreen = [self.camera getNearPlane];
    m_scene->setViewPoint([self.camera getPos]);
    
    float upStep = viewScreen.upLen / self.frameBuffer.height;
    float rightStep = viewScreen.rightLen / self.frameBuffer.width;
    
    float upStartOffset = upStep/2;
    float rightStartOffset = rightStep/2;
    
    // Generate pixels and cast rays
    for(int h = 0; h < self.frameBuffer.height; ++h) {
        VectorF pixelOffsetVec = Math::vec3AXPlusBY(viewScreen.upV, (upStep*h + upStartOffset), viewScreen.rightV, rightStartOffset);
        PointF pixelCenter = Math::vec3APlusB(viewScreen.bottomLeft, pixelOffsetVec);
        
        VectorF rightInc = Math::vec3Scale(viewScreen.rightV, rightStep);
        for (int w = 0; w < self.frameBuffer.width; ++w) {
            VectorF castDir = Math::vec3AMinusB(pixelCenter, [self.camera getPos]);
            Math::vec3Normalize(castDir);
            pixelCenter.increment(rightInc);
            
            Ray r([self.camera getPos], castDir);
            Color c = m_scene->traceRay(r);
            Pixel * p = [self.frameBuffer getPixel:w height:h];
            p->c = c;
        }
    }
    
    NSString *saveFile = options[@"saveFile"];
    
    if (saveFile) {
        // Save Pixel buffer to file
        [self.frameBuffer exportToFile:saveFile
                    format:@""
                     width:100
                    height:100
                   options:@{ @"topRowFirst" : [NSNumber numberWithBool:YES] }
         ];
    }
}

- (void) setFrameBuffer:(FrameBuffer *)fb {
    self->m_fb = fb;
}

-(FrameBuffer*) getFrameBuffer {
    return self->m_fb;
}

- (NSDictionary*)getFrameBufferPixels:(NSDictionary*)options {
    NSData *data = [m_fb getPixels:options];
    
    NSDictionary * d = @{
        @"data" : data,
        @"rowSize": [NSNumber numberWithUnsignedInt:m_fb.width*4],
        @"width" : [NSNumber numberWithUnsignedInt:m_fb.width],
        @"height" : [NSNumber numberWithUnsignedInt:m_fb.height]
    };
    return d;
    
    
}
@end
