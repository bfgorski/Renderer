//
//  RenderManager.m
//  Renderer
//
//  Created by Benjamin Gregorski on 9/8/13.
//
//

#import "RenderManager.h"
#import "Renderer.h"
#import "OpenGLRenderer.h"

@interface RenderManager()

@property(nonatomic) Renderer* activeRenderer;
@property(nonatomic) OpenGLRenderer *openGLRenderer;

@end

@implementation RenderManager

+ (RenderManager*) instance {
    static RenderManager *renderManager;
    if (!renderManager) {
        renderManager = [[RenderManager alloc] init];
    }
    return renderManager;
}

- (RenderManager*) init {
    self = [super init];
    
    if (self) {
        _activeRenderer = [[Renderer alloc] init:@"San Antonio"];
        _openGLRenderer = [[OpenGLRenderer alloc] init];
    }
    
    return self;
}

- (Renderer*) getActiveRenderer {
    return self.activeRenderer;
}

- (OpenGLRenderer*) getOpenGLRenderer {
    return self.openGLRenderer;
}

@end
