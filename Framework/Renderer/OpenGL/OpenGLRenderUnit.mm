//
//  OpenGLRenderUnit.m
//  Renderer
//
//  Created by Benjamin Gregorski on 10/30/13.
//
//

#import "OpenGLRenderUnit.h"
#import "ShaderProgram.h"

#include "VertexBufferObject.h"
#include "PolygonMesh.h"
#include "MaterialParams.h"

using namespace Framework;

@interface OpenGLRenderUnit ()
{
    Framework::OpenGL::VertexBufferObject * m_vbo;
}

@property(nonatomic) ShaderProgram* shaderProgram;
@property(nonatomic) OpenGL::Material* material;

@end

@implementation OpenGLRenderUnit

@synthesize material = m_material;


- (id) initWithShader:(ShaderProgram *)shader material:(OpenGL::Material*)material polygonMesh:(PolygonMesh *)polygonMesh {
    self = [super init];
    
    if (self) {
        self.shaderProgram = shader;
        
        // Generate VBO from PolygnMesh
        m_vbo = new Framework::OpenGL::VertexBufferObject(polygonMesh);
        
        // The Render Unit does not own this.
        m_material = material;
        
        // Get bindings for material parameters from shader Program
        [shader bindMaterial:material];
    }
    
    return self;
}

- (void) dealloc {
    // The RenderUnit owns the vertex buffer object but not the shader.
    if (m_vbo) {
        delete m_vbo;
    }
    _shaderProgram = nil;
    m_material = NULL;
}

- (void) render {
    if (m_material) {
        m_material->setup();
    }
    m_vbo->render();
}

- (BOOL) isValid {
    return (m_vbo && self.shaderProgram);
}

@end
