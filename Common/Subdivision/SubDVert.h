//
//  SubDVert.h
//  BenGRay
//
//  Created by Benjamin Gregorski on 8/21/12.
//
//

#import <Foundation/Foundation.h>

#define SUB_D_VERT_X 0
#define SUB_D_VERT_Y 1
#define SUB_D_VERT_Z 2
#define SUB_D_VERT_W 3

@interface SubDVert : NSObject
{
    unsigned m_index;
    float m_pos[4];
}

@property (nonatomic, assign, getter = getIndex) unsigned Index;
@property (nonatomic, assign) float X;
@property (nonatomic, assign) float Y;
@property (nonatomic, assign) float Z;
@property (nonatomic, assign) float W;

-(float) getComp: (const unsigned) compIndex;
-(void)  setComp: (const unsigned) compIndex value: (float) v;
-(float*) getPos;
-(void) setPos3: (const float*)pos;
-(void) setPos4: (const float*)pos;
-(void) setPos3: (float) x y: (float) y z: (float) z;
-(void) setPos4: (float) x y: (float) y z: (float) z w: (float) w;
-(void) print;

@end
