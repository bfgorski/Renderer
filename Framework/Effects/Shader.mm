//
//  Shader.m
//  Renderer
//
//  Created by Benjamin Gregorski on 10/24/13.
//
//

#import "Shader.h"

@interface Shader()

@property (nonatomic) GLuint shaderHandle;
@property (nonatomic) NSString* resource;
@property (nonatomic) NSString* resourcePath;
@property (nonatomic) NSString* name;
@property (nonatomic) enum ShaderType type;

@end

@implementation Shader

- (id) init {
    return [self initWithResource:nil name:nil type:ShaderType_Vertex];
}

- (id) initWithResource:(NSString *)resource name:(NSString *)name type:(enum ShaderType)type {
    self = [super init];
    
    if (self) {
        _resource = resource;
        _name = name;
        _type = type;
       
        if (_resource) {
            NSString *resourceType = ((ShaderType_Vertex == type) ? @"vsh" : @"fsh");
            _resourcePath = [[NSBundle mainBundle] pathForResource:resource ofType:resourceType];
            
            GLint glShaderType = (ShaderType_Vertex == type) ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;
            if (![Shader compileShader:&_shaderHandle type:glShaderType file:_resourcePath]) {
                _shaderHandle = 0;
                NSLog(@"Failed to compile shader %@ %@\n", resource, _resourcePath);
            }
        }
    }
    
    return self;
}

- (void) dealloc {
    /*
     * From the Open GL ES Docs:
     *
     * If a shader object to be deleted is attached to a program object, it will be flagged for deletion, 
     * but it will not be deleted until it is no longer attached to any program object
     */
    glDeleteShader(self.shaderHandle);
    _shaderHandle = 0;
}

- (BOOL) isValid {
    return (self.shaderHandle > 0);
}

+ (BOOL)compileShader:(GLuint *)shader type:(GLenum)type file:(NSString *)file
{
    GLint status;
    const GLchar *source;
    
    source = (GLchar *)[[NSString stringWithContentsOfFile:file encoding:NSUTF8StringEncoding error:nil] UTF8String];
    if (!source) {
        NSLog(@"%s failed to load %@\n", __FILE__, file);
        return NO;
    }
    
    *shader = glCreateShader(type);
    glShaderSource(*shader, 1, &source, NULL);
    glCompileShader(*shader);
    
#if defined(DEBUG)
    GLint logLength;
    glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetShaderInfoLog(*shader, logLength, &logLength, log);
        NSLog(@"Shader compile log:\n%s", log);
        free(log);
    }
#endif
    
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
    if (status == 0) {
        glDeleteShader(*shader);
        return NO;
    }
    
    return YES;
}

@end
