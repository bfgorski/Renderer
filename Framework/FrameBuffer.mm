//
//  FrameBuffer.m
//  Renderer
//
//  Created by Benjamin Gregorski on 11/18/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/NSData.h>
#import <NSBitmapImageRep.h>
#import "FrameBuffer.h"

using namespace Framework;

@interface FrameBuffer()

@property (readwrite, assign) unsigned int width;
@property (readwrite, assign) unsigned int height;

@end

@implementation FrameBuffer
{
    NSMutableData * m_fb;
}

-(FrameBuffer*) init: (unsigned int) width height: (unsigned int) height
{
    self.width = width;
    self.height = height;
    int fbSize = width*height*sizeof(Pixel);
    m_fb = [NSMutableData dataWithLength:fbSize];
    return self;
}

-(void) setPixel: (unsigned int) w height: (unsigned int) h pixel: (Pixel) p
{
    int offset = h*self.width + w;
    void * fb = [m_fb mutableBytes];
    Pixel * pPixel = (Pixel*)fb;
    pPixel[offset] = p;
}

-(Pixel*) getPixel:(const unsigned int)w height:(const unsigned int)h
{
    int offset = h*self.width + w;
    void * fb = [m_fb mutableBytes];
    Pixel * pPixel = (Pixel*)fb;
    return (pPixel + offset);
}

-(Pixel*) getPixelPtr
{
    void * p = [m_fb mutableBytes];
    return (Pixel*)p;
}

-(BOOL) exportToFile:(NSString *)fileName format:(NSString *)format width:(NSUInteger)width height:(NSUInteger)height {

    NSUInteger bufferSize = [m_fb length];
    void * buffer = malloc(bufferSize);
    memset(buffer, 0, bufferSize);
    
    /*
      Resample the FB to the indicated size.
     
     Filmic tone mapping.
     
     */
    
    
    NSBitmapImageRep *imageRep =
    [[NSBitmapImageRep alloc] initWithBitmapDataPlanes:(unsigned char **)&buffer
                                            pixelsWide:self.width
                                            pixelsHigh:self.height
                                         bitsPerSample:32
                                       samplesPerPixel:4
                                              hasAlpha:YES
                                              isPlanar:NO
                                        colorSpaceName:NSDeviceRGBColorSpace
                                          bitmapFormat:NSAlphaFirstBitmapFormat
                                           bytesPerRow:(self.width * 4)
                                          bitsPerPixel:128];
    
    NSData *pngData = [imageRep representationUsingType:NSPNGFileType
                                             properties:nil];
    
    [pngData writeToFile:@"unitTest.png" atomically:YES];
    return YES;
}

@end
