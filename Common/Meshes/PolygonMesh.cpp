//
//  PolygonMesh.cpp
//  Renderer
//
//  Created by Benjamin Gregorski on 10/26/13.
//
//

#include "PolygonMesh.h"

namespace Framework {
    
    PolygonMesh::PolygonMesh() : m_format(Pos), m_vertexCapacity(0), m_numVertices(0), m_vertices(NULL), m_triCapacity(0), m_numTris(0), m_triangles(NULL) {}
    
    PolygonMesh::PolygonMesh(const unsigned int numVertices, const unsigned int numTris, const VertexFormat format)
    :m_format(format), m_vertexCapacity(numVertices), m_numVertices(0), m_vertices(NULL), m_triCapacity(numTris), m_numTris(0), m_triangles(NULL) {
        m_triangles = new unsigned int[numTris];
        m_vertices = ::operator new(vertexFormatSize()*numVertices);
    }
    
    PolygonMesh::~PolygonMesh() {
        destroy();
    }
    
    void PolygonMesh::init(const unsigned int numVertices, const unsigned int numTris, const Framework::PolygonMesh::VertexFormat format) {
        destroy();
        m_vertexCapacity = numVertices;
        m_triCapacity = numTris;
        m_triangles = new unsigned int[numTris];
        m_vertices = ::operator new(vertexFormatSize()*numVertices);
    }
    
    bool PolygonMesh::isValid() const {
        return (m_triangles && m_vertices);
    }
    
    bool PolygonMesh::addVertices(const void *data, const unsigned int count, const bool realloc) {
        if (m_vertexCapacity <= (m_numVertices + count)) {
            unsigned int vertexSize = vertexFormatSize();
            char * vertOffset = reinterpret_cast<char*>(m_vertices);
            vertOffset += (m_numVertices*vertexSize);
            memcpy(vertOffset, data, count*vertexSize);
            m_numVertices += count;
            return true;
        }
        return false;
    }
    
    bool PolygonMesh::addTriangles(const unsigned int *newTris, const unsigned int count, const bool realloc) {
        if (m_triCapacity <= (m_numTris + count)) {
            unsigned int * triOffset = m_triangles += (sizeof(unsigned int)*3*numTris());
            memcpy(reinterpret_cast<void*>(triOffset), reinterpret_cast<const void*>(newTris), count*3*sizeof(unsigned int));
            m_numTris += count;
            return true;
        }
        return false;
    }
    
    void PolygonMesh::destroy() {
        if (m_vertices) {
            ::operator delete [] (m_vertices);
        }
        
        if (m_triangles) {
            delete [] m_triangles;
        }
        
        m_numTris = m_numVertices = m_triCapacity = m_vertexCapacity = 0;
    }
    
    unsigned int PolygonMesh::vertexFormatSize() const {
        switch (m_format) {
            case Pos:
                return (sizeof(float)*3);
            case PosNorm:
                return (sizeof(float)*6);
            case PosNormTex0:
                return (sizeof(float)*8);
            case PosNormTex0Col0:
                return sizeof(float)*8 + sizeof(char)*4;
            default:
                break;
        }
        return 0;
    }
}