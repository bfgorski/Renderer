//
//  ShaderSetupParams.h
//  Renderer
//
//  Created by Benjamin Gregorski on 10/29/13.
//
//

#ifndef Renderer_ShaderSetupParams_h
#define Renderer_ShaderSetupParams_h

#include <OpenGLES/ES2/gl.h>

enum {
    TEXTURE_PARAM_TYPE_INT = 0,
    TEXTURE_PARAM_TYPE_FLOAT,
    TEXTURE_PARAM_TYPE_FLOAT_V2,
    TEXTURE_PARAM_TYPE_FLOAT_V3,
    TEXTURE_PARAM_TYPE_FLOAT_V4,
    TEXTURE_PARAM_TYPE_SAMPLER,
    
    MAX_TEXTURE_PARAMS = 8,
    MAX_VERTEX_ATTRIBUTES = 5,
};

/**
 * Generic shader parameter
 */
struct ShaderParam {
    char * m_name;
    GLuint m_handle;
    int m_type;
    
    union {
        GLfloat fVal;
        GLfloat *fvVal;
    };
    
    const char * getName() const { return m_name; }
    GLuint getHandle() const { return m_handle; }
    int getType() const { return m_type; }
};

typedef struct ShaderParam ShaderParam;

/**
 * Parameters to control sampler state e.g. GL_TEXTURE_MIN_FILTER.
 */
struct TextureSetupParam {
    
    GLenum getName() const { return m_pname; }
    int getType() const { return m_type; }
    
    // Open GL param type e.g. GL_TEXTURE_MIN_FILTER
    GLenum m_pname;
    
    // int, float or float vector
    int m_type;
    
    union {
        GLfloat fVal;
        GLint iVal;
        GLfloat *fvVal;
        GLint *ivVal;
        GLuint *uivVal;
    };
};

typedef struct TextureSetupParam TextureSetupParam;

/**
 * Array of TextureSetupParam objects
 */
struct TextureSetupParams {
    TextureSetupParams() : m_numParams(0) {}
    
    unsigned int getNumParams() const { return m_numParams; }
    const TextureSetupParam& getParam(const unsigned int i) const { return m_params[i]; }
    
    TextureSetupParam m_params[MAX_TEXTURE_PARAMS];
    unsigned int m_numParams;
};

typedef struct TextureSetupParams TextureSetupParams;

/**
 * All parameters for setting up a texture to render.
 */
struct TextureSamplerParam {
    // Sampler name used to find handle to shader programm texture parameter
    char * m_name;
    
    // Unique identifier to locate texture resource at runtime
    unsigned int m_textureId;
    
    // GL_TEXTURE_1D, GL_TEXTURE_2D etc
    GLenum m_textureType;
    
    // Handle for shader parameter
    GLint  m_handle;
    
    // Handle for texture resource
    GLuint m_resource;
    
    // Index of OpenGL Sampler GL_TEXTURE0 + m_samplerIndex;
    GLuint m_samplerIndex;
    
    TextureSetupParams m_params;
    
    TextureSamplerParam() : m_name(0), m_textureType(GL_TEXTURE_2D), m_handle(0), m_resource(0), m_samplerIndex(0) {}
    
    const char * getName() const { return m_name; }
    unsigned int getTextureId() const { return m_textureId; }
    GLenum getTextureType() const { return m_textureType; }
    GLint getHandle() const { return m_handle; }
    GLuint getResource() const { return m_resource; }
    GLuint getSamplerIndex() const { return m_samplerIndex; }
    
    const TextureSetupParams& getParams() const { return m_params; }
    
    /**
     * Set the handle obtained by bindind the sampler to a shader parameter
     */
    void setHandle(const GLuint h) { m_handle = h; }
    
};

typedef struct TextureSamplerParam TextureSamplerParam;

#endif
