//
//  OpenGLRenderUnit.h
//  Renderer
//
//  Created by Benjamin Gregorski on 10/30/13.
//
//

#import <Foundation/Foundation.h>

#include "PolygonMesh.h"

using namespace Framework;

@class ShaderProgram;

class VertexBufferObject;

@interface OpenGLRenderUnit : NSObject

@property(nonatomic,readonly) ShaderProgram* shaderProgram;
@property(nonatomic,readonly,getter = isValid) BOOL valid;

- (id) initWithShader:(ShaderProgram*)shader polygonMesh:(PolygonMesh*)polygonMesh;


- (void) dealloc;

- (void) render;

@end
