//
//  FrameBuffer.m
//  Renderer
//
//  Created by Benjamin Gregorski on 11/18/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/NSData.h>
#import "FrameBuffer.h"

@implementation FrameBuffer
{
    NSMutableData * m_fb;
    int m_stride;
}

-(void) init: (unsigned int) width height: (unsigned int) height
{
    m_width = width;
    m_height = height;
    int fbSize = width*height*sizeof(Pixel);
    m_stride = width*sizeof(Pixel);
    m_fb = [NSMutableData dataWithLength:fbSize];
}

-(void) setPixel: (unsigned int) w height: (unsigned int) h pixel: (Pixel) p
{
    int offset = h*m_stride + w;
    void * fb = [m_fb mutableBytes];
    Pixel * pPixel = (Pixel*)fb;
    pPixel[offset] = p;
}

-(Pixel*) getPixel:(const unsigned int)w height:(const unsigned int)h
{
    int offset = h*m_stride + w;
    void * fb = [m_fb mutableBytes];
    Pixel * pPixel = (Pixel*)fb;
    return (pPixel + offset);
}

-(Pixel*) getPixelPtr
{
    void * p = [m_fb mutableBytes];
    return (Pixel*)p;
}

@end
