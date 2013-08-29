//
//  SubDFace.h
//  BenGRay
//
//  Created by Benjamin Gregorski on 8/21/12.
//
//

#import <Foundation/Foundation.h>
#import "SubDVert.h"
#import "SubDHalfEdge.h"

@class SubDFaceIterator;

@interface SubDFace : NSObject
{
    unsigned m_index;
    SubDHalfEdge * m_startEdge;
}

@property(nonatomic, assign, getter = getIndex) unsigned index;
@property(nonatomic, retain, getter = getStartEdge) SubDHalfEdge * startEdge;

-(id) init: (unsigned) index se: (SubDHalfEdge*) startEdge;
-(void) print;

@end

@interface SubDFaceIterator : NSObject
{
    SubDFace * m_face;
    SubDHalfEdge * m_startEdge;
    SubDHalfEdge * m_current;
}

@property(nonatomic, readonly, getter = getCurrent) SubDHalfEdge * current;

-(SubDFaceIterator*) init: (SubDFace*) pFace;
-(void) reset;
-(SubDHalfEdge*) next;
-(bool) isValid;
-(void) printCurrent;
-(void) render;

@end