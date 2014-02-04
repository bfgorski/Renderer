//
//  RenderManager.m
//  Renderer
//
//  Created by Benjamin Gregorski on 9/8/13.
//
//

#import "RenderManager.h"
#import "Renderer.h"
#import "OpenGLRenderer.h"
#import "OpenGLRenderUnit.h"
#import "OpenGLTextureResource.h"

#include "Scene.h"
#include "SceneObject.h"
#include "Material.h"

@interface RenderManager()

@property(nonatomic) Renderer* activeRenderer;
@property(nonatomic) OpenGLRenderer *openGLRenderer;

@end

@implementation RenderManager

+ (RenderManager*) instance {
    static RenderManager *renderManager;
    if (!renderManager) {
        renderManager = [[RenderManager alloc] init];
    }
    return renderManager;
}

- (RenderManager*) init {
    self = [super init];
    
    if (self) {
        _activeRenderer = [[Renderer alloc] init:@"San Antonio"];
        _openGLRenderer = [[OpenGLRenderer alloc] init];
    }
    
    return self;
}

- (Renderer*) getActiveRenderer {
    return self.activeRenderer;
}

- (OpenGLRenderer*) getOpenGLRenderer {
    return self.openGLRenderer;
}

- (void) setupOpenGLRenderer {
    Framework::Scene *s = [self.activeRenderer getScene:@""];
    Framework::Scene::Iterator it(s);
    
    for (; it.current(); ++it) {
        Framework::SceneObject *so = (*it);
        if (!so->hasGeo()) {
            so->createGeo();
            
            OpenGL::Material * openGLMaterial = new OpenGL::Material();
            
            // TODO: Initialize OpenGL Materia; from SceneObject's material
            /*const Framework::Material *m = so->getMaterial();
            if (m) {
                ;
            }*/
            
            OpenGLTextureResource *t = [[self getOpenGLRenderer] getTextureResource:[NSNumber numberWithInteger:1] optionalTextureStringId:nil];
            
            static char s[] = "diffuseSampler";
            static char shaderName[] = "Simple Shader";
            
            openGLMaterial->m_shaderProgram = shaderName;
            openGLMaterial->m_numSamplers = 1;
            openGLMaterial->m_samplers = new TextureSamplerParam[1];
            
            openGLMaterial->m_samplers[0].m_textureId = 1;
            openGLMaterial->m_samplers[0].m_name = s;
            openGLMaterial->m_samplers[0].m_handle = t.handle;
            openGLMaterial->m_samplers[0].m_textureType = GL_TEXTURE_2D;
            openGLMaterial->m_samplers[0].m_resource = 0;
            openGLMaterial->m_samplers[0].m_samplerIndex = 0;
            
            TextureSetupParams &p = openGLMaterial->m_samplers[0].m_params;
            p.m_params[0].m_pname = GL_TEXTURE_MIN_FILTER;
            p.m_params[0].m_type = TEXTURE_PARAM_TYPE_INT;
            p.m_params[0].iVal = GL_LINEAR;
            
            p.m_params[1].m_pname = GL_TEXTURE_MAG_FILTER;
            p.m_params[1].m_type = TEXTURE_PARAM_TYPE_INT;
            p.m_params[1].iVal = GL_LINEAR;
            
            p.m_params[2].m_pname = GL_TEXTURE_WRAP_S;
            p.m_params[2].m_type = TEXTURE_PARAM_TYPE_INT;
            p.m_params[2].iVal = GL_REPEAT;
            
            p.m_params[3].m_pname = GL_TEXTURE_WRAP_T;
            p.m_params[3].m_type = TEXTURE_PARAM_TYPE_INT;
            p.m_params[3].iVal = GL_REPEAT;
            
            p.m_numParams = 4;
            
            /**
             * Find the shader program from render manager that this material references
             */
            ShaderProgram *shaderProgram = [[self getOpenGLRenderer] getShaderProgram:[NSString stringWithUTF8String:openGLMaterial->m_shaderProgram] ];
            
            if (shaderProgram) {
                OpenGLRenderUnit * ru = [[OpenGLRenderUnit alloc] initWithShader:shaderProgram material:openGLMaterial polygonMesh:so->getPolygonMesh()];
                [[self getOpenGLRenderer] addRenderUnit:ru];
            } else {
                // TODO: ASSERT that material uses an unknown shader program
            }
        }
    }
    
}

- (void) disableOpenGLRenderer {
    
}

@end
