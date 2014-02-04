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

@class Camera;

/**
 * The Renderer object is used to manage and render a scene.
 */
@interface Renderer : NSObject

/**
 * The Camera from which the scene is rendered from.
 */
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
 * Get a Scene from the Renderer.
 *  Note that Framework::Scene is a c++ object.
 *
 * @param sceneName Unique identifier for the Scene
 * 
 * @return A pointer to the Scene or NULL
 */
- (Framework::Scene*) getScene:(NSString*)sceneName;

/**
 * Update the internal camera for the renderer using the given Camera object.
 */
- (void) updateCamera:(Camera*)camera;

@end
