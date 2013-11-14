//
//  MaterialParams.h
//  Renderer
//
//  Created by Benjamin Gregorski on 11/6/13.
//
//

#ifndef __Renderer__MaterialParams__
#define __Renderer__MaterialParams__

#include "ShaderSetupParams.h"

namespace Framework { namespace OpenGL {
    
    enum MaterialFlags {
        // If set indicates that the shader params were fixed up in place
        SHADER_PARAMS_IN_PLACE = (1 << 0),
        
        // If set indicates that the sampler params were fixed up in place.
        SAMPLER_PARAMS_IN_PLACE = (1 << 1)
    };
    
    /**
     * A Material is a set of parameters to control OpenGL rendering
     */
    struct Material {
        /*
         * An identifier for the shader program to render the material.
         */
        char * m_shaderProgram;
        
        unsigned int m_flags;
        
        unsigned int m_numParams;
        ShaderParam * m_params;
        
        unsigned int m_numSamplers;
        TextureSamplerParam * m_samplers;
        
        Material();
        ~Material();
    
        unsigned int getNumParams() const { return m_numParams; }
        const ShaderParam& getParam(const unsigned int i) const { return m_params[i]; }
        ShaderParam& getParam(const unsigned int i) { return m_params[i]; }
        
        unsigned int getNumSamplers() const { return m_numSamplers; }
        const TextureSamplerParam& getSampler(const unsigned int i) const { return m_samplers[i]; }
        TextureSamplerParam& getSampler(const unsigned int i) { return m_samplers[i]; }
        
        bool getFlag(const enum MaterialFlags flag) const { return (m_flags | flag); }
        void setFlag(const enum MaterialFlags flag) { m_flags |= flag; }
    
        void setup() const ;
    };
}
}


#endif /* defined(__Renderer__MaterialParams__) */
