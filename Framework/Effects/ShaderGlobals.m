//
//  ShaderGlobals.m
//  Renderer
//
//  Created by Benjamin Gregorski on 10/29/13.
//
//

#import <GLKit/GLKit.h>
#import "ShaderGlobals.h"

@implementation ShaderGlobals
{
    /* 
     * Global Model matrix, camera matrix and projection matrix
     * to transform world-space objects into camera screen space
     */
    GLKMatrix4 m_modelViewProjectionMatrix;
    
    /*
     * Indicate which rendering layer to draw
     */
    GLfloat m_renderingOptions[4];
    
    /*
     * Global lighting model with falloff controls
     */
    GLfloat m_lightingModel[4];
    
}

/**
 *
 */
+ (ShaderGlobals*) instance {
    static ShaderGlobals* shaderGlobals;
    
    if (!shaderGlobals) {
        static dispatch_once_t onceToken;
        dispatch_once(&onceToken, ^{
            shaderGlobals = [[ShaderGlobals alloc] init];
        });
    }
    return shaderGlobals;
}

- (void) setModelViewProjectionMatrix:(GLKMatrix4 *)m {
    m_modelViewProjectionMatrix = (*m);
}

- (void) setRenderingMode:(enum RenderingMode)m {
    m_renderingOptions[(int)m] = 1;
}

- (void) setLightingModel:(GLfloat *)lightingModel {
    memcpy(m_lightingModel, lightingModel, sizeof(GLfloat)*4);
}

@end
