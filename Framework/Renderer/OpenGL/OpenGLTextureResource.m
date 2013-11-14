//
//  OpenGLTextureResource.m
//  Renderer
//
//  Created by Benjamin Gregorski on 11/10/13.
//
//

#import "OpenGLTextureResource.h"

@interface OpenGLTextureResource()
{
    // Result of glGenTextures
    GLuint m_textureResource;

    // GL_TEXTURE_1D/2D/3D
    GLenum m_textureType;

    // Texel format (GL_RGBA, GL_RGB etc)
    GLenum m_format;
    
    // GL_FLOAT, GL_UNSIGNED_BYTE etc.
    GLenum m_type;
}

@property (nonatomic, getter = handle) GLuint handle;
@property (nonatomic) unsigned int width;
@property (nonatomic) unsigned int height;
@property (nonatomic) unsigned int levels;

@end

@implementation OpenGLTextureResource

- (id) initWithId:(NSNumber*)textureId textureData:(NSData *)textureData width:(unsigned int)width height:(unsigned int)height levels:(unsigned int)levels {
    return [self initWithId:textureId textureData:textureData width:width height:height levels:levels textureType:GL_TEXTURE_2D format:GL_RGBA dataType:GL_UNSIGNED_BYTE];
}

- (id) initWithId:(NSNumber*)textureId
      textureData:(NSData *)textureData
              width:(unsigned int)width
             height:(unsigned int)height
             levels:(unsigned int)levels
        textureType:(GLenum) textureType
             format:(GLenum)format
               dataType:(GLenum)dataType {
    self = [super init];
    
    if (self) {
        _textureId = textureId;
        _width = width;
        _height = height;
        _levels = levels;
        m_textureType = textureType;
        m_format = format;
        m_type = dataType;
        
        glGenTextures(1, &m_textureResource);
        glBindTexture(m_textureType, m_textureResource);
        glTexImage2D(m_textureType, 0, m_format, width, height, 0, m_format, m_type, [textureData bytes]);
    }
    
    return self;
}

- (GLuint) handle {
    return m_textureResource;
}

- (void) dealloc {
    glDeleteTextures(1, &m_textureResource);
}

@end
