//
//  VertexBufferObject.h
//  Renderer
//
//  Created by Benjamin Gregorski on 10/30/13.
//
//

#ifndef __Renderer__VertexBufferObject__
#define __Renderer__VertexBufferObject__

#include <iostream>
#include <OpenGLES/ES2/gl.h>

// Named vertex attributes for mapping GLKEffects logic to client vertex attrib enables
enum VBOVertexAttrib
{
    VertexAttribPosition = 0,
    VertexAttribNormal,
    VertexAttribColor,
    VertexAttribTexCoord0,
    VertexAttribTexCoord1
} ;

namespace Framework {

    class PolygonMesh;
    
namespace OpenGL {

    /**
     * Data structures to render a model using vertex buffers
     */
    class VertexBufferObject {
        
    public:
        VertexBufferObject();
        
        VertexBufferObject(const PolygonMesh* p);
        VertexBufferObject(PolygonMesh* p);
        
        ~VertexBufferObject();
        
        void render();
        
    private:
        
        VertexBufferObject(const VertexBufferObject&);
        VertexBufferObject& operator=(const VertexBufferObject&) { return (*this); }
        
        void init(const PolygonMesh *p);
        
        // Vertex and index buffers
        GLuint m_vertexArray;
        GLuint m_vertexBuffer;
        
        GLuint m_indexArray;
        GLuint m_indexBuffer;
        GLuint m_numIndices;
        
        GLenum m_primitiveType; // GL_TRIANGLES etc.
        GLenum m_dataType;      // GL_UNSIGNED_INT etc.
        GLenum m_vertexAttribs; // Vertex attributes
        
        const PolygonMesh * m_polgonMesh;
    };
    
}
}

#endif /* defined(__Renderer__VertexBufferObject__) */
