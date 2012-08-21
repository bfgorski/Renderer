//
//  Renderer.h
//  Renderer
//
//  Created by Benjamin Gregorski on 11/14/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//


@interface Renderer : NSObject
{
    NSString * m_name;
    void * m_so;
}

@property(retain,atomic) NSString* name;


-(void) init: (NSString*) name;
-(void) render: (NSString **) options;
-(void) parseOptions;
-(void) runUnitTests;

@end
