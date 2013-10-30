//
//  ShaderProgram+Internal.m
//  Renderer
//
//  Created by Benjamin Gregorski on 10/29/13.
//
//

#import "ShaderProgram+Internal.h"
#import "ShaderProgram_Internal.h"

@implementation ShaderProgram (Internal)

- (void) fetchGlobalUniforms {
    // Get uniform locations for standard shader parameters
    m_globalUniforms[UNIFORM_GLOBAL_RENDERING_OPTIONS] = glGetUniformLocation(m_program, "renderingOptions");
    m_globalUniforms[UNIFORM_GLOBAL_LIGHTING_MODEL] = glGetUniformLocation(m_program, "lightingModel");
    m_globalUniforms[UNIFORM_GLOBAL_MODELVIEWPROJECTION_MATRIX] = glGetUniformLocation(m_program, "modelViewProjectionMatrix");
}

- (void) setGlobalUniforms {
    glUniform4fv(m_globalUniforms[UNIFORM_GLOBAL_RENDERING_OPTIONS], 1, m_renderingOptions);
    glUniform4fv(m_globalUniforms[UNIFORM_GLOBAL_LIGHTING_MODEL], 1, m_lightingModel);
    glUniformMatrix4fv(m_uniforms[UNIFORM_GLOBAL_MODELVIEWPROJECTION_MATRIX], 1, 0, m_modelViewProjectionMatrix.m);
}
@end
