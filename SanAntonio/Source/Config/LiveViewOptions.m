//
//  LiveViewOptions.m
//  Renderer
//
//  Created by Benjamin Gregorski on 10/4/13.
//
//

#import "LiveViewOptions.h"
#import <dispatch/once.h>

static NSString* SHOW_TRACKBALL_BOUNDS = @"ShowTrackballBounds";

@implementation LiveViewOptions

+ (LiveViewOptions*) instance {
    static dispatch_once_t once;
    static LiveViewOptions * liveViewOptions;
    
    dispatch_once(&once, ^{
        liveViewOptions = [[LiveViewOptions alloc] init];
    });
    
    return liveViewOptions;
}

- (LiveViewOptions*) init {
    self = [super init];
    self.showTrackballBounds = YES;
    return self;
}

- (void)encodeWithCoder:(NSCoder *)encoder {
    [encoder encodeBool:self.showTrackballBounds forKey:SHOW_TRACKBALL_BOUNDS];
}

- (id)initWithCoder:(NSCoder *)decoder {
    self.showTrackballBounds = [decoder decodeBoolForKey:SHOW_TRACKBALL_BOUNDS];
    return self;
}


@end
