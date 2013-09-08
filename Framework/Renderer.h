//
//  Renderer.h
//  Renderer
//
//  Created by Benjamin Gregorski on 11/14/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import "FrameBuffer.h"

@interface Renderer : NSObject

@property(retain,atomic) NSString* name;
@property(readonly, getter = getFrameBuffer) const FrameBuffer* frameBuffer;

-(Renderer*) init: (NSString*) name;

/**
 * Render the scene.
 *
 * @param options:
 *          @"saveFile" : Save image to this file
 */
-(void) render: (NSDictionary*) options;

@end
