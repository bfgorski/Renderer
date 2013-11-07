//
//  OpenGLRenderUnit.m
//  Renderer
//
//  Created by Benjamin Gregorski on 10/30/13.
//
//

#import "OpenGLRenderUnit.h"

#include "VertexBufferObject.h"
#include "PolygonMesh.h"

using namespace Framework;

@interface OpenGLRenderUnit ()
{
    Framework::OpenGL::VertexBufferObject * m_vbo;
}

@property(nonatomic) ShaderProgram *shaderProgram;
@property(nonatomic) VertexBufferObject *vbo;

@end

@implementation OpenGLRenderUnit


- (id) initWithShader:(ShaderProgram *)shader polygonMesh:(PolygonMesh *)polygonMesh {
    self = [super init];
    
    if (self) {
        self.shaderProgram = shader;
        
        // Generate VBO from PolygnMesh
        m_vbo = new Framework::OpenGL::VertexBufferObject(polygonMesh);
    }
    
    return self;
}

- (void) dealloc {
    if (m_vbo) {
        delete m_vbo;
    }
}

- (void) render {
    
    // Shader setup stuff from Material is coming
    
    m_vbo->render();
}

- (BOOL) isValid {
    return (self.vbo && self.shaderProgram);
}

@end
