//
//  ShaderProgram+External.h
//  Renderer
//
//  Created by Benjamin Gregorski on 10/29/13.
//
//

#import <GLKit/GLKit.h>
#import "ShaderProgram.h"
#import "ShaderRenderingModes.h"
#import "ShaderSetupParams.h"

/**
 * Methods for setting instance-specific common shader parameters.
 */
@interface ShaderProgram (External)

/**
 * Global Matrix to take world-space coordinates to camera-space screen coordinates.
 */
+ (void) setModelViewProjectionMatrix:(GLKMatrix4*)m;

/**
 * Set the global rendering mode
 */
+ (void) setRenderingMode:(enum RenderingMode) m;

/**
 * Set the parameters for the global lighting model with falloff.
 */
- (void) setLightingModel:(GLfloat*)lightingModel immediately:(BOOL)immediately;

/**
 * World space transform to apply to vertices before final perspective transform.
 */
- (void) setModelMatrix:(GLKMatrix4*)m immediately:(BOOL)immediately;

/**
 * Matrix to transform normal vectors.
 */
- (void) setNormalMatrix:(GLKMatrix3*)m immediately:(BOOL)immediately;

/**
 * If the shader supports the indicate texture setup the appropriate OpenGL parameters.
 *
 * @param texture           Which uniform texture parameter to set.
 * @param textureResource   Integer value from glGenTextures
 * @param samplerNumber     GL_TEXTURE0 + samplerNumber is enabled
 * @param params            OpenGL parameters for this texture
 */
- (void) setupTexture2D:(enum ShaderUniforms)texture textureResource:(GLuint)textureResource samplerNumber:(GLint)samplerNumber params:(TextureSetupParams*)params;

@end
