//
//  SubDVert.m
//  BenGRay
//
//  Created by Benjamin Gregorski on 8/21/12.
//
//

#import "SubDVert.h"

@implementation SubDVert

-(float*) getPos
{
    return m_pos;
}

-(void) setPos3:(const float *)pos
{
    memcpy(m_pos, pos, 3*sizeof(float));
    m_pos[3] = 1;
}

-(void) setPos4:(const float *)pos
{
    memcpy(m_pos, pos, 4*sizeof(float));
}

-(void) setPos3:(float)x y:(float)y z:(float)z
{
    m_pos[0] = x;
    m_pos[1] = y;
    m_pos[2] = z;
    m_pos[3] = 1;
}

-(void) setPos4:(float)x y:(float)y z:(float)z w:(float)w
{
    m_pos[0] = x;
    m_pos[1] = y;
    m_pos[2] = z;
    m_pos[3] = w;
}

@end
