//
//  ShaderGlobals.h
//  Renderer
//
//  Created by Benjamin Gregorski on 10/29/13.
//
//

#import <Foundation/Foundation.h>
#import <ShaderRenderingModes.h>
#import <GLKit/GLKit.h>



/**
 * The ShaderGlobals object provides storage for global shader parameters that are shared across shaders.
 */
@interface ShaderGlobals : NSObject

/**
 * ShaderGlobals is a Singleton object that stores the global parameters.
 */
+ (ShaderGlobals*) instance;

/**
 * ShaderProgram objects ask the ShaderGlobals object to grab handles for the 
 * global uniform parameters and store them in the indicated array.
 */
+ (void) fetchGlobalUniformsFromProgram:(GLuint)shaderProgram handleStore:(GLint*)handleStore;

/**
 * Global Matrix to take world-space coordinates to camera-space screen coordinates.
 */
- (void) setModelViewProjectionMatrix:(GLKMatrix4*)m;

/**
 * Set the global rendering mode
 */
- (void) setRenderingMode:(enum RenderingMode) m;

/**
 * Set the parameters for the global lighting model with falloff.
 */
- (void) setLightingModel:(GLfloat*)lightingModel;

@end
