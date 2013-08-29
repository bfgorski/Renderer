//
//  SubDHalfEdge.h
//  BenGRay
//
//  Created by Benjamin Gregorski on 8/21/12.
//
//

#import <Foundation/Foundation.h>
#import "SubDVert.h"

@class SubDFace;

@interface SubDHalfEdge : NSObject
{
    unsigned m_index;
    
    SubDVert * m_vert;
    SubDHalfEdge * m_edgePair;
    SubDHalfEdge * m_faceEdge;
    SubDFace * m_face;
}

@property(nonatomic, assign, getter = getIndex) unsigned index;
@property(nonatomic, retain, getter = getVert) SubDVert* vert;
@property(nonatomic, retain, getter = getEdgePair) SubDHalfEdge* edgePair;
@property(nonatomic, retain, getter = getFaceEdge) SubDHalfEdge* faceEdge;
@property(nonatomic, retain, getter = getFace) SubDFace* face;


-(id) init: (SubDVert*) v ep: (SubDHalfEdge*) edgePair fe: (SubDHalfEdge*) faceEdge f: (SubDFace*) face;
-(void) print;

@end
