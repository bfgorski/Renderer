//
//  LiveViewOptions.h
//  Renderer
//
//  Created by Benjamin Gregorski on 10/4/13.
//
//

#import <Foundation/Foundation.h>
#import <Foundation/NSCoder.h>

@interface LiveViewOptions : NSObject <NSCoding>

@property (nonatomic) BOOL showTrackballBounds;

/**
 * Get a singleton instance of LiveViewOptions.
 */
+ (LiveViewOptions*) instance;

/**
 * Create a new instance and initialize to default values;
 */
- (LiveViewOptions*) init;

- (void)encodeWithCoder:(NSCoder *)encoder;
- (id)initWithCoder:(NSCoder *)decoder;

@end
