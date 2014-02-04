//
//  OfflineRenderer.h
//  Renderer
//
//  Created by Benjamin Gregorski on 1/22/14.
//
//

#import "Renderer.h"

/**
 * The Renderer object is used to manage and render a scene.
 */
@interface OfflineRenderer : Renderer

-(OfflineRenderer*) init: (NSString*) name;

/**
 * Render the scene.
 *
 * @param options:
 *          @"saveFile" : Save image to this file
 */
-(void) render: (NSDictionary*) options;

/**
 * Convert the Frame Buffer pixels to RGBA.
 *
 * @param options NSDictionary with options to convert Raw FB Data
 - @"ARGB" return ARGB instead of default RGBA
 *
 * @return NSDictionary with data and metadata
 *          @{
 @"data" : NSData object
 @"rowSize" : Bytes per row
 @"width" : 10
 @"height": 20
 }
 */
- (NSDictionary*)getFrameBufferPixels:(NSDictionary*)options;

@end
