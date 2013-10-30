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

static NSString *RENDERING_MODE = @"RenderingMode";

/*
 * X,Y,Z and scalar for quaternion
 */
static NSString *QUAT_X = @"Quat.x";
static NSString *QUAT_Y = @"Quat.y";
static NSString *QUAT_Z = @"Quat.z";
static NSString *QUAT_S = @"Quat.s";

/*
 * Global lighting model parameters
 */
static NSString *LIGHTING_FALLOFF = @"LightingFalloff";

static CGFloat DEFAULT_ZERO_POINT = 0.5;

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
        _showTrackballBounds = YES;
        _wireframe = NO;
        _camera = nil;
        _lightingFalloff = DEFAULT_ZERO_POINT;
    }
   
    return self;
}

- (void) initWithViewOptions:(LiveViewOptions*)viewOptions {
    self.showTrackballBounds = viewOptions.showTrackballBounds;
    self.wireframe = viewOptions.wireframe;
    self.camera = viewOptions.camera;
    self.renderingMode = viewOptions.renderingMode;
    self.lightingFalloff = viewOptions.lightingFalloff;
}

- (void)encodeWithCoder:(NSCoder *)encoder {
    [encoder encodeBool:self.showTrackballBounds forKey:SHOW_TRACKBALL_BOUNDS];
    [encoder encodeBool:self.wireframe forKey:WIREFRAME];
    
    // Encode quaternion rotation
    [encoder encodeFloat:self.trackBall.x() forKey:QUAT_X];
    [encoder encodeFloat:self.trackBall.y() forKey:QUAT_Y];
    [encoder encodeFloat:self.trackBall.z() forKey:QUAT_Z];
    [encoder encodeFloat:self.trackBall.s() forKey:QUAT_S];
    
    if (self.camera) {
        [encoder encodeObject:self.camera forKey:CAMERA];
    }
    
    [encoder encodeInt:self.renderingMode forKey:RENDERING_MODE];
    
    // Encode component of global lighting model
    [encoder encodeFloat:self.lightingFalloff forKey:LIGHTING_FALLOFF];
}

- (id)initWithCoder:(NSCoder *)decoder {
    self.showTrackballBounds = [decoder decodeBoolForKey:SHOW_TRACKBALL_BOUNDS];
    self.wireframe = [decoder decodeBoolForKey:WIREFRAME];
    
    float x = [decoder decodeFloatForKey:QUAT_X];
    float y = [decoder decodeFloatForKey:QUAT_Y];
    float z = [decoder decodeFloatForKey:QUAT_Z];
    float s = [decoder decodeFloatForKey:QUAT_S];
    
    self.trackBall.set(s,x,y,z);
    
    if (self.camera) {
        Camera * c = [decoder decodeObjectForKey:CAMERA];
        [self.camera copyFromCamera:c];
    } else {
        self.camera = [decoder decodeObjectForKey:CAMERA];
    }
    
    self.renderingMode = (RenderingMode)[decoder decodeIntForKey:RENDERING_MODE];
    
    // Encode component of global lighting model
    self.lightingFalloff = [decoder decodeFloatForKey:LIGHTING_FALLOFF];

    return self;
}

+ (NSUInteger) getNumRenderingModes {
    return NumRenderingModes;
}

+ (NSString*) getDescriptionForRenderingMode:(NSUInteger)renderingMode {
    switch (renderingMode) {
        case 0:
            return @"Standard";
        case 1:
            return @"Diffuse Lighting";
        case 2:
            return @"Diffuse Color";
        case 3:
            return @"Normal";
        default:
            break;
    }
    return @"";
}

/**
 * The LiveViewOptions class serves as UIPickerViewDataSource for the RenderingMode
 */
- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView {
    return 1;
}

- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component {
    return [LiveViewOptions getNumRenderingModes];
}




















@end
