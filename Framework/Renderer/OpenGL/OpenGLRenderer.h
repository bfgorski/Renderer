//
//  OpenGLRenderer.h
//  Renderer
//
//  Created by Benjamin Gregorski on 10/30/13.
//
//

#import <Foundation/Foundation.h>

@class OpenGLRenderUnit;

@interface OpenGLRenderer : NSObject

- (id) init;

- (void) dealloc;

- (void) addRenderUnit:(OpenGLRenderUnit*)renderUnit;

- (void) render;

@end
