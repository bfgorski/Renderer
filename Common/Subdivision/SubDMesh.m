//
//  SubDMesh.m
//  BenGRay
//
//  Created by Benjamin Gregorski on 8/21/12.
//
//

#import "SubDMesh.h"
#import "SubDVert.h"
#import "SubDHalfEdge.h"
#import "SubDFace.h"

@implementation SubDMesh

@synthesize levels=m_levels;

-(SubDMesh*) init
{
    m_faces = [NSMutableArray array];
    m_verts = [NSMutableArray array];
    m_edges = [NSMutableArray array];
    
    return self;
}

-(void) print
{
    NSLog(@"SubDMesh::print\n");
    
    for (SubDVert *pVert in m_verts) {
        [pVert print];
    }
}

-(bool) loadFile:(const char *)f
{
    m_faces = [[NSMutableArray alloc] init ];
    
    NSLog(@"Loading SubDMesh File %s\n", f);
    return true;
}

-(void) createCube:(float)sideLength
{
    /*
     X,Y,Z positions for a cube
     */
    static const float cubeVerts[8][3] = {
        {-1, -1, -1},
        { 1, -1, -1},
        { 1,  1, -1},
        {-1,  1, -1},
        {-1, -1,  1},
        { 1, -1,  1},
        { 1,  1,  1},
        {-1,  1,  1},
    };
    
    /*
     * Face orientation using right hand rule
     */
    static const float cubeFaces[6][4] = {
        {0,3,2,1},
        {4,5,6,7},
        {1,2,6,5},
        {3,6,4,7},
        {2,3,7,6},
        {0,1,5,4}
    };
    
    // create verts
    for (int i = 0; i < 8; ++i) {
        [self addVertex: cubeVerts[i][0] y:cubeVerts[i][1] z:cubeVerts[i][2]];
    }

    // create faces
    for (int i = 0; i < 6; ++i) {
        [self addQuad: cubeFaces[i][0] v1:cubeFaces[i][1] v2:cubeFaces[i][2] v3:cubeFaces[i][3]];
    }

    [m_faces enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        [obj print];
    }];
}

-(bool) addVertex:(float)x y:(float)y z:(float)z
{
    SubDVert * pVert = [SubDVert alloc];
    
    /*
     * This creates a new top-level vertex with no parents.
     */
    unsigned newVertIndex = [m_verts count];
    [pVert setPos4:x y:y z:z w:1];
    [pVert setIndex:newVertIndex];
    
    [m_verts addObject:pVert];
    
    NSLog(@"AddVertex %.2f %.2f %.2f %d\n", x, y, z, newVertIndex);

    return true;
}

-(bool) addTriangle:(unsigned int)v0 v1:(unsigned int)v1 v2:(unsigned int)v2
{
    return true;
}

-(bool) addQuad:(unsigned int)v0 v1:(unsigned int)v1 v2:(unsigned int)v2 v3:(unsigned int)v3
{
    NSLog(@"Adding Quad %d %d %d %d\n", v0, v1, v2, v3);
    
    SubDVert * pVert[4];
    pVert[0] = [m_verts objectAtIndex:v0];
    pVert[1] = [m_verts objectAtIndex:v1];
    pVert[2] = [m_verts objectAtIndex:v2];
    pVert[2] = [m_verts objectAtIndex:v3];
    
    SubDFace * pFace = [SubDFace alloc];

    SubDHalfEdge * pHalfEdges[4];
    
    // Create half edges
    for (int i = 0; i < 4; ++i) {
        pHalfEdges[i] = [[SubDHalfEdge alloc] init:pVert[i] ep:NULL fe:NULL f:pFace];
        [m_edges addObject:pHalfEdges[i]];
    }
    
    // connect half edges and find edge pair.
    for (int i = 0 ; i < 4; ++i) {
        
        // the face edge pointer points in the opposite direction of the vertex pointer
        unsigned faceEdgeIndex = (3-i);
        SubDHalfEdge * pFaceEdge = pHalfEdges[faceEdgeIndex];
        [pHalfEdges[i] setFaceEdge:pFaceEdge];
        
        unsigned index0 = [pHalfEdges[i] getIndex];
        unsigned index1 = [pFaceEdge getIndex];
        
        NSLog(@"New Half Edge %d %d\n", index0, index1);
        
        // find a half edge that points to a vertex with index1 and whose face pointer
        // points to index 0. This is the half-dge pair that goes with the new half-edge
        for (SubDHalfEdge * pHalfEdge in m_edges) {
            SubDHalfEdge * pFaceHalfEdge = [pHalfEdge getFaceEdge];
            SubDVert * pHalfEdgeVert = [pHalfEdge getVert];
            
            if (index1 == [pHalfEdgeVert getIndex] &&
                (index0 == pFaceHalfEdge.getVert.getIndex) ) {
                
                [pHalfEdges[i] setEdgePair:pHalfEdge];
                
                NSLog(@"Found Half Edge Pair %d %d\n", index1, index0);
                break;
            }
        }
    }
    
    [m_faces addObject:pFace];
    
    return true;
}



-(void) subDivide
{
    
}

-(void) render:(const SubDMeshRenderOptions *)options
{
    // iterate around each face and render a polygon
    glBegin(GL_QUADS);
    
    for (SubDFace *pFace in m_faces) {
        [pFace print];
    }
    
    
    glEnd();
}

@end
