//
//  ShaderSetupParams.h
//  Renderer
//
//  Created by Benjamin Gregorski on 10/29/13.
//
//

#ifndef Renderer_ShaderSetupParams_h
#define Renderer_ShaderSetupParams_h

enum {
    TEXTURE_PARAM_TYPE_INT = 0,
    TEXTURE_PARAM_TYPE_FLOAT = 1,
    TEXTURE_PARAM_TYPE_FLOAT_V = 2,
    
    MAX_TEXTURE_PARAMS = 8,
};

struct TextureSetupParam {
    GLenum m_pname;
    int m_type; // int, float or float vector
    
    union {
        GLfloat fVal;
        GLint iVal;
        GLfloat *fvVal;
        GLint *ivVal;
        GLuint *uivVal;
    };
};

typedef struct TextureSetupParam TextureSetupParam;

struct TextureSetupParams {
    TextureSetupParam m_params[MAX_TEXTURE_PARAMS];
    unsigned int m_numParams;
};

typedef struct TextureSetupParams TextureSetupParams;

#endif
