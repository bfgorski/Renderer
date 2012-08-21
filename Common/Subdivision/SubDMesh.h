//
//  SubDMesh.h
//  BenGRay
//
//  Created by Benjamin Gregorski on 8/21/12.
//
//

#import <Foundation/Foundation.h>

@interface SubDMesh : NSObject
{
    int m_levels;
}

@property(getter = getLevels, setter = setLevels:) int m_levels;

-(void) print;
-(bool) loadFile: (const char*) f;
-(void) subDivide;
@end
