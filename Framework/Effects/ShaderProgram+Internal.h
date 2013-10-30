//
//  ShaderProgram+Internal.h
//  Renderer
//
//  Created by Benjamin Gregorski on 10/29/13.
//
//

#import "ShaderProgram.h"

@interface ShaderProgram (Internal)

/**
 * Fetch handles for global uniform parameters.
 */
- (void) fetchGlobalUniforms;

/**
 * Set global uniform parameters that this shader uses.
 */
- (void) setGlobalUniforms;

@end
