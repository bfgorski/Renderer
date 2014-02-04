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
@class Camera;

@interface OpenGLRenderer : NSObject

/**
 * If set, this Camera will be used to render the scene.
 */
@property(strong, nonatomic) Camera* camera;

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
 * Determine if there is a shader program with the given name.
 */
- (ShaderProgram*) getShaderProgram:(NSString*)programName;

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

/**
 * Render the scene from the current camera
 */
- (void) render;

/**
 * Remove render units and cleanup OpenGL resources.
 */
- (void) tearDownGL;
@end
