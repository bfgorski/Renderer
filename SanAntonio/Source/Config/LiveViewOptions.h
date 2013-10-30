//
//  LiveViewOptions.h
//  Renderer
//
//  Created by Benjamin Gregorski on 10/4/13.
//
//

#import <Foundation/Foundation.h>
#import <Foundation/NSCoder.h>
#import "ShaderRenderingModes.h"

#include "Quat.h"

using namespace Framework::Math;

@class Camera;

@interface LiveViewOptions : NSObject <NSCoding, UIPickerViewDataSource>

@property (nonatomic) BOOL showTrackballBounds;
@property (nonatomic) BOOL wireframe;

@property (nonatomic, assign) RenderingMode renderingMode;

/**
 * Global lighting control 
 */
@property (nonatomic, assign) float lightingFalloff;

/**
 * Current trackball rotation.
 */
@property (nonatomic, assign) Quat trackBall;

/**
 * Record the camera parameters
 */
@property (nonatomic, strong) Camera* camera;

/**
 * Get a singleton instance of LiveViewOptions.
 */
+ (LiveViewOptions*) instance;

/**
 * Create a new instance and initialize to default values;
 */
- (LiveViewOptions*) init;

/**
 * Initialize with existing values.
 */
- (void) initWithViewOptions:(LiveViewOptions*)viewOptions;

- (void)encodeWithCoder:(NSCoder *)encoder;
- (id)initWithCoder:(NSCoder *)decoder;

/**
 * Number of elements in RenderingMode enum class.
 */
+ (NSUInteger) getNumRenderingModes;

/**
 * String that can be used for UI display.
 */
+ (NSString*) getDescriptionForRenderingMode:(NSUInteger)renderingMode;

- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView;

@end
