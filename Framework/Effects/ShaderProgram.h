//
//  ShaderProgram.h
//  Renderer
//
//  Created by Benjamin Gregorski on 10/24/13.
//
//

#import <Foundation/Foundation.h>
#import "Shader.h"

/**
*  Uniform shader parameters shared across all shaders
*  and set on a per-frame basis.
*/
enum GlobalShaderUniforms
{
    UNIFORM_GLOBAL_MODELVIEWPROJECTION_MATRIX = 0,
    UNIFORM_GLOBAL_RENDERING_OPTIONS,
    
    NUM_GLOBAL_UNIFORMS,
    MAX_GLOBAL_UNIFORMS = 20
};

/*
 * Uniform index for parameters common to all shaders.
 * but used on a per-instance basis.
 */
enum ShaderUniforms
{
    UNIFORM_NORMAL_MATRIX = 0,
    UNIFORM_MODEL_MATRIX,
    UNIFORM_DIFFUSE_TEXTURE,
    UNIFORM_LIGHTING_MODEL,
    
    NUM_UNIFORMS,
    MAX_UNIFORMS = 20
};

@interface ShaderProgram : NSObject

@property (nonatomic,readonly) NSString* name;
@property (nonatomic,readonly) Shader* vertexShader;
@property (nonatomic,readonly) Shader* fragmentShader;

/**
 * A ShaderProgram is valid only when a valid program has
 * been created from vertex and pixel shaders.
 */
@property (nonatomic,readonly,getter = isValid) BOOL valid;

/**
 * Initialize with the given vertex and fragment shaders.
 */
- (id) initWithName:(NSString*)name vertexShader:(Shader*)vertexShader fragmentShader:(Shader*)fragmentShader;

/**
 * Initialize with the given vertex and fragment shaders.
 */
- (id) initWithName:(NSString *)name vertexShaderPath:(NSString *)vsp fragmentShaderPath:(NSString *)fsp;

/**
 * Detach shaders and mark for deletion
 */
- (void) dealloc;

/**
 * Check if the shader supports the given uniform parameter
 */
- (BOOL) supportsUniform:(enum ShaderUniforms)shaderUniform;

/**
 * Set this program as the current enabled vertex and fragment shaders
 * and setup global uniform parameters.
 */
- (BOOL) enable;

/*
 * Set shader-specific uniform parameters. Shaders derived from ShaderProgam override this
 * to implement shader specific functionality.
 */
- (void) setUniforms;

@end
