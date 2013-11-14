//
//  MaterialParams.cpp
//  Renderer
//
//  Created by Benjamin Gregorski on 11/6/13.
//
//

#include "MaterialParams.h"
#include <OpenGLES/ES2/gl.h>

namespace Framework { namespace OpenGL {
 
    Material::Material() : m_flags(0), m_numParams(0), m_numSamplers(0) {}
    Material::~Material() {
        if (!(SHADER_PARAMS_IN_PLACE & m_flags)) {
            ;
        }
        
        if (!(SAMPLER_PARAMS_IN_PLACE & m_flags)) {
            ;
        }
    }
    
    void Material::setup() const {
        glEnable(GL_TEXTURE_2D);
        
        for (unsigned int i = 0; i < m_numSamplers; ++i) {
            // Setup params for this sampler
            const TextureSamplerParam& sampler = m_samplers[i];
            
            for (unsigned int curParam = 0; curParam < sampler.getParams().getNumParams(); ++curParam) {
                const TextureSetupParam& setupParam = sampler.getParams().getParam(curParam);
                glTexParameteri(GL_TEXTURE_2D, setupParam.getName(), setupParam.iVal);
            }
            
            glActiveTexture(GL_TEXTURE0 + sampler.getSamplerIndex()); // samplerNumber);
            glBindTexture(GL_TEXTURE_2D, sampler.getResource()); // textureResource);
            glUniform1i(sampler.getHandle() /*m_uniforms[texture]*/, sampler.getSamplerIndex()); // samplerNumber);

        }
    }
}
}