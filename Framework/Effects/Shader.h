//
//  Shader.h
//  Renderer
//
//  Created by Benjamin Gregorski on 10/24/13.
//
//

#import <Foundation/Foundation.h>

enum ShaderType { ShaderType_Vertex, ShaderType_Fragment };

@interface Shader : NSObject

@property (nonatomic,readonly) GLuint shaderHandle;
@property (nonatomic,readonly) NSString* resource;
@property (nonatomic,readonly) NSString* resourcePath;
@property (nonatomic,readonly) NSString* name;
@property (nonatomic,readonly) enum ShaderType type;

/*
 * Check that the shaderHandle is valid.
 */
@property (nonatomic,readonly,getter = isValid) BOOL valid;

- (id) init;

/**
 * Load a shader using a resource from the main bundle and attempt to compile it
 */
- (id) initWithResource:(NSString*)resource name:(NSString*)name type:(enum ShaderType)type;

/**
 * Mark the shader obect for deletion
 */
- (void) dealloc;

/**
 * Compile the shader indicated by type and file and store the shader handle in "shader".
 */
+ (BOOL) compileShader:(GLuint *)shader type:(GLenum)type file:(NSString *)file;


@end
