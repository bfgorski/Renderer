//
//  LiveViewOptions.h
//  Renderer
//
//  Created by Benjamin Gregorski on 10/4/13.
//
//

#import <Foundation/Foundation.h>
#import <Foundation/NSCoder.h>

@class Camera;

@interface LiveViewOptions : NSObject <NSCoding>

@property (nonatomic) BOOL showTrackballBounds;
@property (nonatomic) BOOL wireframe;

/**
 * Record the last camera position
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

@end
