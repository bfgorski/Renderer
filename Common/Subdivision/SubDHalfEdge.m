//
//  SubDHalfEdge.m
//  BenGRay
//
//  Created by Benjamin Gregorski on 8/21/12.
//
//

#import "SubDHalfEdge.h"
#import "SubDFace.h"

@implementation SubDHalfEdge

@synthesize index=m_index;
@synthesize vert=m_vert;
@synthesize edgePair=m_edgePair;
@synthesize faceEdge=m_faceEdge;
@synthesize face=m_face;

-(id) init:(SubDVert *)v ep:(SubDHalfEdge *)edgePair fe:(SubDHalfEdge *)faceEdge f:(SubDFace *)face {
        
    self->m_vert = v;
    self->m_edgePair = edgePair;
    self->m_faceEdge = faceEdge;
    self->m_face = face;
    
    return self;
}

-(void) print {
    NSLog(@"Ind %d V %d EP %d FE %d F %d\n",
          m_index,
          [m_vert getIndex],
          [m_edgePair getIndex],
          [m_faceEdge getIndex],
          [m_face getIndex]
    );
}

@end
