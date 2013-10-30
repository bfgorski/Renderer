//
//  PolygonMesh.h
//  Renderer
//
//  Created by Benjamin Gregorski on 10/26/13.
//
//

#ifndef __Renderer__PolygonMesh__
#define __Renderer__PolygonMesh__

#include <iostream>

namespace Framework {
    
    class PolygonMesh {
    public:
        
        /**
         * Vertex formats supported by the PolygonMesh.
         * Pos, Norm, Tex are floats. Col are bytes.
         */
        enum VertexFormat { Pos, PosNorm, PosNormTex0, PosNormTex0Col0 };
        
        /**
         * Create an unitialized polygon mesh.
         */
        PolygonMesh();
        
        PolygonMesh(const unsigned int numVertices, const unsigned int numTris, const VertexFormat format);
        
        virtual ~PolygonMesh();
        
        /**
         * Delete existing mesh and reinitialize with the given parameters
         */
        void init(const unsigned int numVertices, const unsigned int numTris, const VertexFormat format);
        
        /**
         * Return true if vertices and triangles have been successfully allocated.
         */
        bool isValid() const;
        
        /**
         * Add the indicated number of vertices. 
         * The format must correspond to the format indicate during PolygonMesh construction.
         * 
         * @return false is returned if the allocated number of vertices is exceeded.
         */
        bool addVertices(const void * data, const unsigned int count, const bool realloc = false);
        
        /**
         * Add the indicated number of triangles.
         *
         * @return false is returned of the allocated number of vertices is exceeded
         */
        bool addTriangles(const unsigned int * t, const unsigned int numTris, const bool realloc = false);
        
        VertexFormat vertexFormat() const { return m_format; }
        
        unsigned int vertCapacity() const { return m_vertexCapacity; }
        unsigned int numVertices() const { return m_numVertices; }
        unsigned int triCapacity() const { return m_triCapacity; }
        unsigned int numTris() const { return m_numTris; }
        
        /**
         * Access the raw vertex data.
         */
        const void * getVerts() const { return m_vertices; }
        
        /**
         * Access the raw triangle data.
         */
        const unsigned int * getTris() const { return m_triangles; }
        
    private:
        
        /**
         * Delete the existing mesh data and reset capacities and counts.
         */
        void destroy();
        
        unsigned int vertexFormatSize() const;
        
        VertexFormat m_format;
        
        /**
         * Number of vertices that space has been allocated for.
         */
        unsigned int m_vertexCapacity;
        
        /**
         * Number of vertices added.
         */
        unsigned int m_numVertices;
        
        /**
         * Vertex Data
         */
        void * m_vertices;
        
        /**
         * Number of triangles that space has been allocated for.
         */
        unsigned int m_triCapacity;
        
        /**
         * Number of triangles added.
         */
        unsigned int m_numTris;
            
        /**
         * Three consecutive vertices are a triangle
         */
        unsigned int * m_triangles;
    };
}

#endif /* defined(__Renderer__PolygonMesh__) */
