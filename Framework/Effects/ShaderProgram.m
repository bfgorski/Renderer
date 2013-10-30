//
//  ShaderProgram.m
//  Renderer
//
//  Created by Benjamin Gregorski on 10/24/13.
//
//

#import <GLKit/GLKEffects.h>
#import "ShaderProgram.h"
#import "ShaderProgram_Internal.h"

@implementation ShaderProgram

- (id) init {
    self = [super init];
    
    if (self) {
        ;
    }
    return self;
}

- (id) initWithName:(NSString*)name vertexShader:(Shader *)vertexShader fragmentShader:(Shader *)fragmentShader {
    self = [super init];
    
    if (self && vertexShader.valid && fragmentShader.valid) {
        m_program = glCreateProgram();
        _name = name;
        _vertexShader = vertexShader;
        _fragmentShader = fragmentShader;
        
        if (![self initializeProgram]) {
            NSLog(@"%s failed to initialize program\n", __FILE__);
        }
    } else {
        NSLog(@"%s Invalid parameters for shader program creation\n", __FILE__);
    }
   
    return self;
}

- (id) initWithName:(NSString *)name vertexShaderPath:(NSString *)vsp fragmentShaderPath:(NSString *)fsp {
    Shader * vs = [[Shader alloc] initWithResource:vsp name:vsp type:ShaderType_Vertex];
    Shader * fs = [[Shader alloc] initWithResource:fsp name:fsp type:ShaderType_Fragment];
        
    return [self initWithName:name vertexShader:vs fragmentShader:fs];
}

- (void) dealloc {
    // Release vertex and fragment shaders.
    if (self.vertexShader) {
        glDetachShader(m_program, self.vertexShader.shaderHandle);
        //glDeleteShader(vertShader);
    }
    
    if (self.fragmentShader) {
        glDetachShader(m_program, self.fragmentShader.shaderHandle);
        //glDeleteShader(fragShader);
    }
}

- (BOOL) supportsUniform:(enum ShaderUniforms)shaderUniform {
    return (0 < m_uniforms[shaderUniform]);
}

- (BOOL) enable {
    if (self.valid) {
        glUseProgram(m_program);
        [self setGlobalUniforms];
        return YES;
    }
    return NO;
}

- (BOOL) initializeProgram {
    // Attach vertex shader to program.
    glAttachShader(m_program, _vertexShader.shaderHandle);
    
    // Attach fragment shader to program.
    glAttachShader(m_program, _fragmentShader.shaderHandle);
    
    // Bind attribute locations.
    // This needs to be done prior to linking.
    glBindAttribLocation(m_program, GLKVertexAttribPosition, "position");
    glBindAttribLocation(m_program, GLKVertexAttribNormal, "normal");
    
    // Link program.
    if (![self linkProgram:m_program]) {
        NSLog(@"Failed to link program: %@ %d", self.name, m_program);
        
        if (_vertexShader) {
            glDeleteShader(_vertexShader.shaderHandle);
            _vertexShader = nil;
        }
        if (_fragmentShader) {
            glDeleteShader(_fragmentShader.shaderHandle);
            _fragmentShader = nil;
        }
        if (m_program) {
            glDeleteProgram(m_program);
            m_program = 0;
        }
        
        return NO;
    }
    
    [self fetchGlobalUniforms];
    
    m_uniforms[UNIFORM_MODEL_MATRIX] = glGetUniformLocation(m_program, "modelMatrix");
    m_uniforms[UNIFORM_NORMAL_MATRIX] = glGetUniformLocation(m_program, "normalMatrix");
    m_uniforms[UNIFORM_DIFFUSE_TEXTURE] = glGetUniformLocation(m_program, "diffuseSampler");
    m_uniforms[UNIFORM_LIGHTING_MODEL] = glGetUniformLocation(m_program, "lightingModel");
    
    // Release vertex and fragment shaders.
    /*if (vertShader) {
        glDetachShader(_program, vertShader);
        glDeleteShader(vertShader);
    }
    if (fragShader) {
        glDetachShader(_program, fragShader);
        glDeleteShader(fragShader);
    }*/
    
    return YES;
}

- (BOOL)linkProgram:(GLuint)prog
{
    GLint status;
    glLinkProgram(prog);
    
#if defined(DEBUG)
    GLint logLength;
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(prog, logLength, &logLength, log);
        NSLog(@"Program link log:\n%s", log);
        free(log);
    }
#endif
    
    glGetProgramiv(prog, GL_LINK_STATUS, &status);
    if (status == 0) {
        return NO;
    }
    
    return YES;
}

- (BOOL)validateProgram:(GLuint)prog
{
    GLint logLength, status;
    
    glValidateProgram(prog);
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(prog, logLength, &logLength, log);
        NSLog(@"Program validate log:\n%s", log);
        free(log);
    }
    
    glGetProgramiv(prog, GL_VALIDATE_STATUS, &status);
    if (status == 0) {
        return NO;
    }
    
    return YES;
}

- (BOOL) isValid {
    return (0 != m_program);
}

- (void) setUniforms {
    glUniformMatrix4fv(m_uniforms[UNIFORM_MODEL_MATRIX], 1, 0, m_modelMatrix.m);
    glUniformMatrix3fv(m_uniforms[UNIFORM_NORMAL_MATRIX], 1, 0, m_normalMatrix.m);
}

- (void) fetchGlobalUniforms {
    // Get uniform locations for standard shader parameters
    m_globalUniforms[UNIFORM_GLOBAL_RENDERING_OPTIONS] = glGetUniformLocation(m_program, "renderingOptions");
    m_globalUniforms[UNIFORM_GLOBAL_MODELVIEWPROJECTION_MATRIX] = glGetUniformLocation(m_program, "modelViewProjectionMatrix");
}

- (void) setGlobalUniforms {
    glUniform4fv(m_globalUniforms[UNIFORM_GLOBAL_RENDERING_OPTIONS], 1, m_renderingOptions);
    glUniformMatrix4fv(m_uniforms[UNIFORM_GLOBAL_MODELVIEWPROJECTION_MATRIX], 1, 0, m_modelViewProjectionMatrix.m);
}

@end
