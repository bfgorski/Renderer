//
//  FrameBuffer.h
//  Renderer
//
//  Created by Benjamin Gregorski on 11/18/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "BasicTypes.h"

/**
    2D Framebuffer where top left is 0,0 and bottom right is (width-1), (height-1).
 */
@interface FrameBuffer : NSObject
{
    int m_width;
    int m_height;
}

-(void) init: (unsigned int) width height: (unsigned int) height;
-(void) setPixel: (unsigned int) w height: (unsigned int) h pixel: (Pixel) p;
-(Pixel*) getPixel: (const unsigned int) w height: (const unsigned int) h;
-(Pixel*) getPixelPtr;

@end
