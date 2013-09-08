//
//  main.m
//  Renderer
//
//  Created by Benjamin Gregorski on 11/14/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "Renderer.h"

int main (int argc, const char * argv[])
{
    @autoreleasepool {
        Renderer * myRenderer = [Renderer alloc];
        [myRenderer init: @"Bens Renderer"];
        NSDictionary *options = @{
            @"saveFile" : @"/Users/bfgorski/image.png"
        };
        [myRenderer render:options];
        [myRenderer release];
    }
    return 0;
}

