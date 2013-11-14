//
//  OpenGLRenderer.m
//  Renderer
//
//  Created by Benjamin Gregorski on 10/30/13.
//
//

#import "OpenGLRenderer.h"
#import "OpenGLRenderUnit.h"
#import "OpenGLTextureResource.h"
#import "ShaderProgram.h"

#include "MaterialParams.h"

using namespace Framework;

@interface OpenGLRenderer()
{
    NSMutableArray * m_renderUnits;
    NSMutableDictionary * m_textureResources;
    NSMutableDictionary * m_shaders;
    
    // Dictionary of render units by renderUnitId property
    NSMutableDictionary * m_renderUnitDict;
}

@end

@implementation OpenGLRenderer

- (id) init {
    self = [super init];
    
    if (self) {
        m_renderUnits = [[NSMutableArray alloc] initWithCapacity:10];
        m_textureResources = [[NSMutableDictionary alloc] init];
        m_shaders = [[NSMutableDictionary alloc] init];
    }
    return self;
}

- (void) dealloc {
    
}

- (void) addRenderUnit:(OpenGLRenderUnit *)renderUnit {
    /*
     * Attach texture resource handles to sampler parameters
     */
    OpenGL::Material *m = renderUnit.material;
    
    for (unsigned int i = 0; i < m->getNumSamplers(); ++i) {
        TextureSamplerParam& t = m->getSampler(i);
        t.m_resource = [self getTextureResourceHandle:t.getTextureId()];
    }
    
    [m_renderUnits addObject:renderUnit];
}

- (void) addTextureResource:(OpenGLTextureResource *)textureResource {
    [m_textureResources setObject:textureResource forKey:textureResource.textureId];
}

- (BOOL) addShaderProgram:(ShaderProgram *)shaderProgram {
    if ([m_shaders objectForKey:shaderProgram.name]) {
        return NO;
    }
    
    [m_shaders setObject:shaderProgram forKey:shaderProgram.name];
    return YES;
}

- (OpenGLTextureResource*) getTextureResource:(NSNumber *)textureId optionalTextureStringId:(NSString *)stringId {
    return [m_textureResources objectForKey:textureId];
}

- (GLuint) getTextureResourceHandle:(unsigned int)textureId {
    NSNumber * key = [NSNumber numberWithUnsignedInt:textureId];
    OpenGLTextureResource *t = [m_textureResources objectForKey:key];
    return (t ? t.handle : 0);
}

- (void) render {
    for(OpenGLRenderUnit* renderUnit in m_renderUnits) {
        [renderUnit render];
    }
}

- (void) tearDownGL {
    // Tear down renderunits
    [m_renderUnits removeAllObjects];
    
    // Tear down texture resources
    [m_textureResources removeAllObjects];
    
    // Tear down shaders
    [m_shaders removeAllObjects];
}




@end
