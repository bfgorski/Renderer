//
//  RenderManager.m
//  Renderer
//
//  Created by Benjamin Gregorski on 9/8/13.
//
//

#import "RenderManager.h"
#import "Renderer.h"

@interface RenderManager()

@property(strong, nonatomic) Renderer* activeRenderer;

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
    self.activeRenderer = [[Renderer alloc] init:@"San Antonio"];
    return self;
}

- (Renderer*) getActiveRenderer {
    return self.activeRenderer;
}

@end
