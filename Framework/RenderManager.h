//
//  RenderManager.h
//  Renderer
//
//  Created by Benjamin Gregorski on 9/8/13.
//
//

#import <Foundation/Foundation.h>

@class Renderer;
@class OpenGLRenderer;

/**
 * The RenderManager object controls one or more Renderer objects
 */
@interface RenderManager : NSObject

/**
 * Get an instance of a RenderManager
 */
+ (RenderManager*) instance;

/**
 * Initialize an instance of a RenderManager with a Renderer object.
 */
- (RenderManager*) init;

/**
 * Get the Renderer object marked as active.
 */
- (Renderer*) getActiveRenderer;

/**
 * Render a scene using OpenGL
 */
- (OpenGLRenderer*) getOpenGLRenderer;
@end
