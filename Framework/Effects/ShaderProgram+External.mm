//
//  ShaderProgram+External.m
//  Renderer
//
//  Created by Benjamin Gregorski on 10/29/13.
//
//

#import "ShaderProgram+External.h"
#import "ShaderProgram_Internal.h"

@implementation ShaderProgram (External)

+ (void) setModelViewProjectionMatrix:(GLKMatrix4 *)m {
    memcpy((void*)(&m_modelViewProjectionMatrix), m, sizeof(GLKMatrix4));
}

+ (void) setRenderingMode:(enum RenderingMode)m {
    memset(m_renderingOptions, 0, 4*sizeof(unsigned int));
    m_renderingOptions[(int)m] = 1;
}

- (void) setLightingModel:(GLfloat *)lightingModel immediately:(BOOL)immediately {
    if (immediately) {
        glUniform4fv(m_uniforms[UNIFORM_LIGHTING_MODEL], 1, lightingModel);
    } else {
        memcpy(m_lightingModel, lightingModel, sizeof(GLfloat)*4);
    }
}

- (void) setModelMatrix:(GLKMatrix4 *)matrix immediately:(BOOL)immediately{
    if (immediately) {
        glUniformMatrix4fv(m_uniforms[UNIFORM_MODEL_MATRIX], 1, 0, matrix->m);
    } else {
        memcpy(&m_modelMatrix, matrix, sizeof(GLKMatrix4));
    }
}

- (void)setNormalMatrix:(GLKMatrix3 *)matrix immediately:(BOOL)immediately{
    if (immediately) {
        glUniformMatrix3fv(m_uniforms[UNIFORM_NORMAL_MATRIX], 1, 0, matrix->m);
    } else {
        memcpy(&m_normalMatrix, matrix, sizeof(GLKMatrix4));
    }
}

- (void)setupTexture2D:(enum ShaderUniforms)texture textureResource:(GLuint)textureResource samplerNumber:(GLint)samplerNumber params:(TextureSetupParams *)params {
    if (![self supportsUniform:texture]) {
        return;
    }
    
    glEnable(GL_TEXTURE_2D);
    
    if (params) {
        for (unsigned int i = 0; i < params->m_numParams; ++i) {
            glTexParameteri(GL_TEXTURE_2D, params->m_params[i].m_pname, params->m_params[i].iVal);
        }
    }
    
    glActiveTexture(GL_TEXTURE0 + samplerNumber);
    glBindTexture(GL_TEXTURE_2D, textureResource);
    glUniform1i(m_uniforms[texture], samplerNumber);
}

@end
