//
//  OpenGLRenderer.h
//  Renderer
//
//  Created by Benjamin Gregorski on 10/30/13.
//
//

#import <Foundation/Foundation.h>

@class ShaderProgram;
@class OpenGLRenderUnit;
@class OpenGLTextureResource;

@interface OpenGLRenderer : NSObject

- (id) init;

- (void) dealloc;

/**
 * Add a RenderUnit to be rendered
 */
- (void) addRenderUnit:(OpenGLRenderUnit*)renderUnit;

/**
 * Add a TextureResource that can be used by a RenderUnit.
 */
- (void) addTextureResource:(OpenGLTextureResource*)textureResource;

/**
 * Add the shader to renderer.
 *
 * @return YES/NO if a shader with the same name already exists
 */
- (BOOL) addShaderProgram:(ShaderProgram*)shaderProgram;

/**
 * Find a texture resource by Id
 */
- (OpenGLTextureResource*) getTextureResource:(NSNumber*)textureId
                      optionalTextureStringId:(NSString*) stringId;

/**
 * Get the handle for the texture resource from glGenTextures().
 *
 * @param textureId The "textureId" field from a TextureSamplerParam object.
 */
- (GLuint) getTextureResourceHandle:(unsigned int)textureId;

- (void) render;

/**
 * Remove render units and cleanup OpenGL resources.
 */
- (void) tearDownGL;
@end
