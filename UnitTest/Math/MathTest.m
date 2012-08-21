//
//  MathTest.m
//  Renderer
//
//  Created by Benjamin Gregorski on 1/18/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "MathTest.h"

#import <Cocoa/Cocoa.h>
//#import "application_headers" as required

@implementation MathTest

// All code under test is in the Application
- (void)testApp
{
    id yourApplicationDelegate = [NSApplication sharedApplication];
    STAssertNotNil(yourApplicationDelegate, @"NSApplication failed to find the shared application");
}

@end
