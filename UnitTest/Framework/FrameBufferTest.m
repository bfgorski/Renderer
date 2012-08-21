//
//  FrameBufferTest.m
//  Renderer
//
//  Created by Benjamin Gregorski on 1/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "FrameBufferTest.h"
#import <Cocoa/Cocoa.h>

@implementation FrameBufferTest
{
    
}

// All code under test is in the Application
- (void)testApp
{
    id yourApplicationDelegate = [NSApplication sharedApplication];
    STAssertNotNil(yourApplicationDelegate, @"NSApplication failed to find the shared application");
    
    FrameBuffer * fb = [FrameBuffer alloc];
    [fb init:1024 height:768];
    
    Pixel p;
    for(unsigned int w = 0 ; w < fb->m_width; ++w) {
        for(unsigned int h = 0; h < fb->m_height; ++h) {
            p.p[0] = 0;
            p.p[1] = 1;
            p.p[2] = 2;
            p.p[3] = 3;
            [fb setPixel:w height:h pixel:p];
        }
    }
    
    for(unsigned int w = 0 ; w < fb->m_width; ++w) {
        for(unsigned int h = 0; h < fb->m_height; ++h) {
            p = [fb getPixel:w height:h];
            if (0 != p.p[0] || 1 != p.p[1] || 2 != p.p[2] || 3 != p.p[3] ) {
                STAssert();
            }             
        }
    }    
}

-(void)testFrameBuffer
{
    [self testApp];
}
@end
