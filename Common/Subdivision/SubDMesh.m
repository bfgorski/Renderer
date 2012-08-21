//
//  SubDMesh.m
//  BenGRay
//
//  Created by Benjamin Gregorski on 8/21/12.
//
//

#import "SubDMesh.h"

@implementation SubDMesh

@synthesize m_levels;

-(void) print {
    NSLog(@"SubDMesh::print\n");
}

-(bool) loadFile:(const char *)f {
    NSLog(@"Loading SubDMesh File %s\n", f);
    return true;
}

-(void) subDivide {
    
}

@end
