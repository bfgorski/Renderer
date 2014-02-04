//
//  OfflineRenderer.m
//  Renderer
//
//  Created by Benjamin Gregorski on 1/22/14.
//
//

#import <ImageIO/ImageIO.h>
#import "OfflineRenderer.h"

#import "Renderer.h"
#import "FrameBuffer.h"
#include "BasicTypesImpl.h"

using namespace Framework;

@interface OfflineRenderer()

@property(strong, setter = setFrameBuffer:, getter = getFrameBuffer) FrameBuffer* frameBuffer;

@end

@implementation Renderer
{
    Scene * m_scene;
}

@synthesize name;
@synthesize frameBuffer = m_fb;

-(OfflineRenderer*) init: (NSString*) n
{
    self = [super init:n];
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

@end

