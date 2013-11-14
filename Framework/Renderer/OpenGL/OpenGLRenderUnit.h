//
//  OpenGLRenderUnit.h
//  Renderer
//
//  Created by Benjamin Gregorski on 10/30/13.
//
//

#import <Foundation/Foundation.h>

#include "PolygonMesh.h"
#include "MaterialParams.h"

using namespace Framework;

@class ShaderProgram;

class VertexBufferObject;

@interface OpenGLRenderUnit : NSObject

@property(nonatomic,readonly) ShaderProgram* shaderProgram;
@property(nonatomic,readonly,getter = isValid) BOOL valid;
@property(nonatomic,readonly) OpenGL::Material* material;

/**
 * A unique id for the render unit
 */
@property(nonatomic,readonly) NSUInteger renderUnitId;

/**
 * Create a new render unit given a ShaderProgram (vertx + fragment shader) Material (Open GL rendering parameters) and a PolygonMesh.
 * The Render unit does not own the shader, material or polygon mesh.
 *
 * ShaderProgram is an Obj-C object.
 * Material and PolygonMesh are C++ objects.
 */
- (id) initWithShader:(ShaderProgram*)shader material:(OpenGL::Material*)material polygonMesh:(PolygonMesh*)polygonMesh;

- (void) dealloc;

- (void) render;

@end
