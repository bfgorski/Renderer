//
//  VertexBufferObject.cpp
//  Renderer
//
//  Created by Benjamin Gregorski on 10/30/13.
//
//

#include "VertexBufferObject.h"
#include "PolygonMesh.h"
#include <OpenGLES/ES2/glext.h>

#ifndef BUFFER_OFFSET
    #define BUFFER_OFFSET(i) ((char *)NULL + (i))
#endif

namespace Framework { namespace OpenGL {
    
    VertexBufferObject::VertexBufferObject()
    : m_vertexArray(0), m_vertexBuffer(0), m_indexArray(0), m_indexBuffer(0) {}
        
    VertexBufferObject::VertexBufferObject(const PolygonMesh*  p) {
        init(p);
    }

    VertexBufferObject::VertexBufferObject(PolygonMesh* p) {
        init( const_cast<const PolygonMesh*>(p));
    }

    VertexBufferObject::~VertexBufferObject() {
        // Cleanup vertex buffer object
        glDeleteBuffers(1, &m_vertexBuffer);
        glDeleteVertexArraysOES(1, &m_vertexArray);
        
        glDeleteBuffers(1, &m_indexBuffer);
    }

    void VertexBufferObject::init(const PolygonMesh *polygonMesh) {
        m_polgonMesh = polygonMesh;
        glGenVertexArraysOES(1, &m_vertexArray);
        glBindVertexArrayOES(m_vertexArray);
        
        glGenBuffers(1, &m_vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
        
        glBufferData(GL_ARRAY_BUFFER, polygonMesh->vertSize(), polygonMesh->getRawVerts(), GL_STATIC_DRAW);
        
        glEnableVertexAttribArray(VBOVertexAttrib::VertexAttribPosition);
        glVertexAttribPointer(VBOVertexAttrib::VertexAttribPosition, 3, GL_FLOAT, GL_FALSE, 24, BUFFER_OFFSET(0));
        glEnableVertexAttribArray(VBOVertexAttrib::VertexAttribNormal);
        glVertexAttribPointer(VBOVertexAttrib::VertexAttribNormal, 3, GL_FLOAT, GL_FALSE, 24, BUFFER_OFFSET(12));
        
        glBindVertexArrayOES(m_vertexArray);
        
        glGenBuffers(1, &m_indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, polygonMesh->triMemSize(), polygonMesh->getTris(), GL_STATIC_DRAW);
        
        m_numIndices = polygonMesh->numTris()*3;
    }
    
    void VertexBufferObject::render() {
        glBindVertexArrayOES(m_vertexArray);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
        glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, (void*)0);
    }
    
}
}