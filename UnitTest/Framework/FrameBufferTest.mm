//
//  FrameBufferTest.m
//  Renderer
//
//  Created by Benjamin Gregorski on 1/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "FrameBufferTest.h"
#import <Cocoa/Cocoa.h>
//#import <NSBitmapImageRep.h>

using namespace Framework;

@implementation FrameBufferTest
{
    
}

// All code under test is in the Application
- (void)testApp
{
    id yourApplicationDelegate = [NSApplication sharedApplication];
    STAssertNotNil(yourApplicationDelegate, @"NSApplication failed to find the shared application");
    
    FrameBuffer * fb = [FrameBuffer alloc];
    [fb init:10 height:10];
    
    Pixel p;
    for(unsigned int w = 0 ; w < fb.width; ++w) {
        for(unsigned int h = 0; h < fb.height; ++h) {
            p.c.c[0] = 0;
            p.c.c[1] = 1;
            p.c.c[2] = 2;
            p.c.c[3] = 3;
            [fb setPixel:w height:h pixel:p];
        }
    }
    
    for(unsigned int w = 0 ; w < fb.width; ++w) {
        for(unsigned int h = 0; h < fb.height; ++h) {
            p = (*[fb getPixel:w height:h]);
            if (0 != p.c.c[0] || 1 != p.c.c[1] || 2 != p.c.c[2] || 3 != p.c.c[3] ) {
                STFail(@"Framebuffer Set Failed\n");
            }             
        }
    }    
}

-(void)testFrameBuffer
{
    NSArray * imageTypes = [NSImage imageFileTypes];
   
    int imageWidth = 64;
    int imageHeight = 64;
    
    void * buffer = malloc(4*imageWidth*imageHeight);
    memset(buffer, 100, 4*imageWidth*imageHeight);
    
    NSBitmapImageRep *imageRep =
    [[NSBitmapImageRep alloc] initWithBitmapDataPlanes:(unsigned char **)&buffer
                                            pixelsWide:imageWidth
                                            pixelsHigh:imageHeight
                                         bitsPerSample:8
                                       samplesPerPixel:4
                                              hasAlpha:YES
                                              isPlanar:NO
                                        colorSpaceName:NSDeviceRGBColorSpace
                                          bitmapFormat:NSAlphaFirstBitmapFormat
                                           bytesPerRow:imageWidth * 4
                                          bitsPerPixel:32];
    NSData *pngData = [imageRep representationUsingType:NSPNGFileType
                                             properties:nil];
    
    [pngData writeToFile:@"unitTest.png" atomically:YES];
    //[self testApp];
   
}
@end
