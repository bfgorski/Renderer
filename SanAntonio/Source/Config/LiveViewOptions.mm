//
//  LiveViewOptions.m
//  Renderer
//
//  Created by Benjamin Gregorski on 10/4/13.
//
//

#import <dispatch/once.h>
#import "LiveViewOptions.h"
#import "Camera.h"

static NSString *SHOW_TRACKBALL_BOUNDS = @"ShowTrackballBounds";
static NSString *WIREFRAME = @"WireFrame";
static NSString *CAMERA = @"Camera";

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
    
    if (self) {
        self.showTrackballBounds = YES;
        self.wireframe = NO;
        self.camera = nil;
    }
   
    return self;
}

- (void) initWithViewOptions:(LiveViewOptions*)viewOptions {
    self.showTrackballBounds = viewOptions.showTrackballBounds;
    self.wireframe = viewOptions.wireframe;
}

- (void)encodeWithCoder:(NSCoder *)encoder {
    [encoder encodeBool:self.showTrackballBounds forKey:SHOW_TRACKBALL_BOUNDS];
    [encoder encodeBool:self.wireframe forKey:WIREFRAME];
    
    if (self.camera) {
        [encoder encodeObject:self.camera forKey:CAMERA];
    }
}

- (id)initWithCoder:(NSCoder *)decoder {
    self.showTrackballBounds = [decoder decodeBoolForKey:SHOW_TRACKBALL_BOUNDS];
    self.wireframe = [decoder decodeBoolForKey:WIREFRAME];
    
    if (self.camera) {
        Camera * c = [decoder decodeObjectForKey:CAMERA];
        [self.camera copyFromCamera:c];
    } else {
        self.camera = [decoder decodeObjectForKey:CAMERA];
    }
    return self;
}

@end
