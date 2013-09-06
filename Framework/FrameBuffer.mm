//
//  FrameBuffer.m
//  Renderer
//
//  Created by Benjamin Gregorski on 11/18/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/NSData.h>
#import <AppKit/NSBitmapImageRep.h>
#import "FrameBuffer.h"
#import "BasicTypesImpl.h"

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

-(BOOL) exportToFile:(NSString *)fileName
              format:(NSString *)format
               width:(NSUInteger)width
              height:(NSUInteger)height
             options:(NSDictionary *)options
{
    unsigned int numPixels = self.width*self.height;
    unsigned int compPerPixel = 4;
    unsigned int bytesPerComp = 1;
    unsigned int outputPixelSize = compPerPixel*bytesPerComp;
    unsigned int outputBufferSize = numPixels*outputPixelSize;
    unsigned char *buffer = (unsigned char*)malloc(outputBufferSize);
   
    id topRowFirst = options[@"topRowFirst"];
    
    /*
      Resample the FB to the indicated size.
     
      Filmic tone mapping.
     
     */
    Pixel* pixels = [self getPixelPtr];
    unsigned int outputIndex;
    for (int i = 0; i < numPixels; ++i) {
        Pixel *pixel = &pixels[i];
    
        if (topRowFirst) {
            // pixel (row,column) is stored at pixel (self.height - 1 - row) + column;
            unsigned int currentRow = (i / self.width);
            unsigned int column = i - (currentRow*self.width);
            unsigned int newRow = self.height - 1 - currentRow;
            outputIndex = newRow*self.width + column;
        } else {
            outputIndex = i;
        }
        
        unsigned char *finalPixel = buffer + (outputIndex*outputPixelSize);
       
        for (int iComp = 0; iComp < 4; ++iComp) {
            finalPixel[iComp] = 255*Math::clamp(pixel->c.c[iComp], 0, 1);
        }
    }
    
    NSBitmapImageRep *imageRep =
    [[NSBitmapImageRep alloc] initWithBitmapDataPlanes:(unsigned char **)&buffer
                                            pixelsWide:self.width
                                            pixelsHigh:self.height
                                         bitsPerSample:8
                                       samplesPerPixel:4
                                              hasAlpha:YES
                                              isPlanar:NO
                                        colorSpaceName:NSDeviceRGBColorSpace
                                          bitmapFormat:0 //RGBA not NSAlphaFirstBitmapFormat=ARGB
                                           bytesPerRow:(self.width*4)
                                          bitsPerPixel:32];
    
    NSData *pngData = [imageRep representationUsingType:NSPNGFileType
                                             properties:nil];
    
    [pngData writeToFile:fileName atomically:YES];
    return YES;
}

@end
