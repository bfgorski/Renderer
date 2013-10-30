//
//  ContentGenerator.h
//  Renderer
//
//  Created by Benjamin Gregorski on 10/24/13.
//
//

#import <Foundation/Foundation.h>
#include "BasicTypes.h"

@interface ContentGenerator : NSObject

/**
 * Generate an RGBA8 checkerboard texture.
 */
+ (NSData*) genCheckerTexture:(Framework::Color)color0
                       color1:(Framework::Color)color1
                        width:(NSInteger)w
                       height:(NSInteger)h
                widthTileSize:(NSInteger)wts
               heightTileSize:(NSInteger) hts;
@end
