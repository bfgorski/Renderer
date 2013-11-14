//
//  OpenGLTextureResource.h
//  Renderer
//
//  Created by Benjamin Gregorski on 11/10/13.
//
//

#import <Foundation/Foundation.h>
#import <GLKit/GLKit.h>

/**
 * The OpenGLTextureResource stores data for a texture
 */
@interface OpenGLTextureResource : NSObject

/**
 * Unique identifier for this texture
 */
@property (nonatomic) NSNumber* textureId;

/**
 * Human readable id for debugging purposes;
 */
@property (nonatomic) NSString* textureStringId;

/**
 * Handle to texture resource for setting texturing parameters
 */
@property (nonatomic,readonly,getter = handle) GLuint handle;
@property (nonatomic,readonly) unsigned int width;
@property (nonatomic,readonly) unsigned int height;

/**
 * Number of mip levels.
 */
@property (nonatomic,readonly) unsigned int levels;

/**
 * Init Texture Resource with data and assume the type is GL_TEXTURE_2D, format is GL_RGBA and data type is GL_UNSIGNED_BYTE
 */
- (id) initWithId:(NSNumber*)textureId textureData:(NSData*)textureData width:(unsigned int)width height:(unsigned int)height levels:(unsigned int)levels;

/**
 * Init Texture Resource with data and specify the format and data type
 */
- (id) initWithId:(NSNumber*)textureId
      textureData:(NSData*)textureData
              width:(unsigned int)width
             height:(unsigned int)height
             levels:(unsigned int)levels
        textureType:(GLenum) textureType
             format:(GLenum) format
               dataType:(GLenum) dataType;

/**
 * Remove OpenGL resources for the texture
 */
- (void) dealloc;

@end
