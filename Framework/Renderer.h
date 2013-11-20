//
//  Renderer.h
//  Renderer
//
//  Created by Benjamin Gregorski on 11/14/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

namespace Framework {
    class Scene;
}

@class FrameBuffer;
@class Camera;

/**
 * The Renderer object is used to manage and render a scene.
 */
@interface Renderer : NSObject

@property(strong, nonatomic, readonly) Camera* camera;
@property(retain,atomic) NSString* name;

-(Renderer*) init: (NSString*) name;

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

/**
 * Get a Scene from the Renderer.
 *  Note that Framework::Scene is a c++ object.
 *
 * @param sceneName Unique identifier for the Scene
 * 
 * @return A pointer to the Scene or NULL
 */
- (Framework::Scene*) getScene:(NSString*)sceneName;

@end
