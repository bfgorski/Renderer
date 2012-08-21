//
//  SubDVert.h
//  BenGRay
//
//  Created by Benjamin Gregorski on 8/21/12.
//
//

#import <Foundation/Foundation.h>

@interface SubDVert : NSObject
{
    float m_pos[4];
}

-(float*) getPos;
-(void) setPos3: (const float*)pos;
-(void) setPos4: (const float*)pos;
-(void) setPos3: (float) x y: (float) y z: (float) z;
-(void) setPos4: (float) x y: (float) y z: (float) z w: (float) w;

@end
