//
//  SubDFace.m
//  BenGRay
//
//  Created by Benjamin Gregorski on 8/21/12.
//
//

#import "SubDFace.h"
#import <GLKit/GLKit.h>

@implementation SubDFace

@synthesize index=m_index;
@synthesize startEdge=m_startEdge;

-(id) init:(unsigned int)index se:(SubDHalfEdge *)startEdge {
    m_index = index;
    m_startEdge = startEdge;
    return self;
}

-(void) print
{
    SubDFaceIterator * pIt = [[SubDFaceIterator alloc] init:self];
    
    while ([pIt isValid]) {
        [pIt printCurrent];
        [pIt next];
    }
    return;
}

@end

@implementation SubDFaceIterator

@synthesize current=m_current;

-(SubDFaceIterator*) init:(SubDFace *)pFace
{
    m_face = pFace;
    [self reset];
    return self;
}

-(void) reset
{
    m_startEdge = [m_face getStartEdge];
    m_current = m_startEdge;
}

-(SubDHalfEdge*) next
{
    // Follow the face iterator around until
    // we get back to the face's starting edge
    m_current = [m_current getFaceEdge];
    
    if (m_current == m_startEdge) {
        m_current = NULL;
    }
    return m_current;
}

-(bool) isValid
{
    return (NULL != m_current);
}

-(void) printCurrent
{
    NSLog(@"Face %d Start %d Cur %d\n",
          [m_face getIndex],
          [m_startEdge getIndex],
          (m_current ? [m_current getIndex] : 0)
    );
}

@end