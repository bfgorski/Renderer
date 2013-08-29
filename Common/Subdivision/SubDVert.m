//
//  SubDVert.m
//  BenGRay
//
//  Created by Benjamin Gregorski on 8/21/12.
//
//

#import "SubDVert.h"

@implementation SubDVert

@synthesize Index=m_index;


-(float) getX {
    return [self getComp:SUB_D_VERT_X];
}

-(void) setX:(float)X {
    m_pos[SUB_D_VERT_X] = X;
}

-(float) getY {
    return [self getComp:SUB_D_VERT_Y];
}

-(void) setY:(float)Y {
    m_pos[SUB_D_VERT_Y] = Y;
}

-(float) getZ {
    return [self getComp:SUB_D_VERT_Z];
}

-(void) setZ:(float)Z {
    m_pos[SUB_D_VERT_Z] = Z;
}

-(float) getW {
    return [self getComp:SUB_D_VERT_W];
}

-(void) setW:(float)W {
    m_pos[SUB_D_VERT_W] = W;
}

-(float) getComp:(const unsigned int) compIndex
{
    return m_pos[compIndex];
}

-(void) setComp:(const unsigned int)compIndex value:(float)v
{
    m_pos[compIndex] = v;
}

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

-(void) print {
    NSLog(@"V %d %.2f %.2f %.2f %.2f\n",
          self->m_index, m_pos[0], m_pos[1], m_pos[2], m_pos[3]
    );
}
@end
