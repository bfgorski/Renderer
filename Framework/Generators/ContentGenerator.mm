//
//  ContentGenerator.m
//  Renderer
//
//  Created by Benjamin Gregorski on 10/24/13.
//
//

#import "ContentGenerator.h"
#include "TextureGenerator.h"

@implementation ContentGenerator

/**
* Generate an RGBA8 checkerboard texture.
*/
+ (NSData*) genCheckerTexture:(Framework::Color)color0
                       color1:(Framework::Color)color1
                        width:(NSInteger)w
                       height:(NSInteger)h
                widthTileSize:(NSInteger)wts
               heightTileSize:(NSInteger) hts {
                   
    NSInteger textureSize = w*h*4;
    void * rawData = malloc(textureSize);
    Framework::Texture::genCheckerColorTexture(color0, color1, w, h, wts, hts, rawData);
    return [NSData dataWithBytesNoCopy:rawData length:textureSize];
}

@end
