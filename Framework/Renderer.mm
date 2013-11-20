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
#include "Box.h"

#include "BasicTypesImpl.h"
#include "PointLightSource.h"  
#include "SimpleMaterial.h"

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

-(Renderer*) init: (NSString*) n
{
    self = [super init];
    /*
     Camera (0,0,10) looking at 0,0,0
     Sphere at (0,0,0) radius 5.
     
     Light at (0,0,10)
     */
    PointF camPos(10,10,0);
    
    // Camera looking toward origin
    VectorF camDir(-1,-1,0);
    Math::vec3Normalize(camDir);
    
    Ray r(camPos, camDir);
    VectorF up(-1,1,0);
    Math::vec3Normalize(up);
    
    self.camera = [[Camera alloc] initWithRay:r upV:up Fov:45 AspectRatio:1.0f nearPlane:5.0f farPlane:100];
    self.frameBuffer = [[FrameBuffer alloc] init:200 height:200];

    m_scene = new Scene();
    self.name  = n;
    
    vec3 pos(-3,0,2);
    Sphere * so = new Sphere(2.0f, pos);
    
    vec3 pos1(3,0,-2);
    Sphere * sphere1 = new Sphere(2.0f, pos1);
    
    // Box centered at origin
    Frame boxFrame(PointF(0,0,0), VectorF(1,0,0), VectorF(0,1,0), VectorF(0,0,1));
    Box * b = new Box(boxFrame,5,5,5);
    Material *boxMat = new SimpleMaterial(Color(0.0,0.0,0.5,1), Color(1,0,0), 50.0f, Color(0,0,0,1));
    b->setMaterial(boxMat);
    
    PointF planePos(0, -10, 0);
    VectorF planeN(0,1,0);
    Plane * plane = new Plane(planePos, planeN);
    
    // SimpleMaterial(const Color& d, const Color& s, const float specExp, const Color& a);
    
    Material *sphereMat = new SimpleMaterial(Color(0.5,0.5,0.5,1), Color(0,1,0,1), 50.0f, Color(0,0,0,1));
    so->setMaterial(sphereMat);
    
    Material *sphereMat1 = new SimpleMaterial(Color(0.5,0.5,0.5,1), Color(1,1,1,1), 50.0f, Color(0,0,0,1));
    sphere1->setMaterial(sphereMat1);
    
    Material *planeMat = new SimpleMaterial(Color(0.3,0.3,0.3,1), Color(0,0.0,0,1), 50.0f, Color(0,0,0,1));
    plane->setMaterial(planeMat);
    
    Color ambient(0,0,0,1);
    Color diffuse(0.5,0.5,0.5,1);
    Color specular(0.2,0.2,0.2,0);
    
    PointF lightPos(5,5,0);
    PointLightSource *p0 = new PointLightSource(lightPos, ambient, diffuse, specular, 1.0f);
    m_scene->addLight(p0);
 
    Color diffuse2(0.2,0.2,0.2,1);
    Color specular2(1,1,1,0);

    PointF light2Pos(-5,5,0);
    PointLightSource* p1 = new PointLightSource(light2Pos, ambient, diffuse2, specular2, 1.0f);
    m_scene->addLight(p1);
    
    m_scene->addSceneObject(b);
    //m_scene->addSceneObject(so);
    //m_scene->addSceneObject(sphere1);
    m_scene->addSceneObject(plane);
    
    return self;
}

-(void) render: (NSDictionary*) options
{
    // Grab view screen from camera and cast rays
    // through pixel centers.
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

- (Framework::Scene*) getScene:(NSString *)sceneName {
    return m_scene;
}









@end
