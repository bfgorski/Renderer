//
//  SubDMesh.h
//  BenGRay
//
//  Created by Benjamin Gregorski on 8/21/12.
//
//

#import <Foundation/Foundation.h>
#import "SubDMeshRenderOptions.h"
#import <GLKit/GLKit.h>

@interface SubDMesh : NSObject
{
    unsigned m_levels;
    
    /*
     * Faces, verts, and edges of the base mesh.
     */
    NSMutableArray * m_faces;
    NSMutableArray * m_verts;
    NSMutableArray * m_edges;
    
    NSSet * m_allFaces;
    NSSet * m_allVerts;
    NSSet * m_allEdges;
}

@property() unsigned levels;

-(SubDMesh*) init;
-(void) print;
-(bool) loadFile: (const char*) f;
-(void) createCube: (float)sideLength;

-(bool) addVertex: (float) x y: (float) y z: (float) z;
-(bool) addTriangle: (unsigned) v0 v1: (unsigned) v1 v2: (unsigned) v2;
-(bool) addQuad: (unsigned) v0 v1: (unsigned) v1 v2: (unsigned) v2 v3: (unsigned) v3;

-(void) subDivide;
-(void) render: (const SubDMeshRenderOptions*) options;

@end

