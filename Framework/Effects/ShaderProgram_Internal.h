//
//  ShaderProgram_Internal.h
//  Renderer
//
//  Created by Benjamin Gregorski on 10/29/13.
//
//

#import "ShaderProgram.h"
#import "ShaderGlobals.h"

/*
 * Global Model matrix, camera matrix and projection matrix
 * to transform world-space objects into camera screen space
 */
static GLKMatrix4 m_modelViewProjectionMatrix;

/*
 * Indicate which rendering layer to draw
 */
static GLfloat m_renderingOptions[4];

@interface ShaderProgram ()
{
    GLuint m_program;
    
    GLint m_globalUniforms[NUM_GLOBAL_UNIFORMS];
    
    /*
     * Handles for shared uniform parameters across all shaders
     */
    GLint m_uniforms[MAX_UNIFORMS];
    
    // Model matrix
    GLKMatrix4 m_modelMatrix;
    
    // Transform normal vectors
    GLKMatrix3 m_normalMatrix;
    
    /*
     * Global lighting model with falloff controls
     */
    GLfloat m_lightingModel[4];
}

@end
