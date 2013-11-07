//
//  OpenGLRenderer.m
//  Renderer
//
//  Created by Benjamin Gregorski on 10/30/13.
//
//

#import "OpenGLRenderer.h"
#import "OpenGLRenderUnit.h"

@interface OpenGLRenderer()
{
    NSMutableArray * m_renderUnits;
}

@end

@implementation OpenGLRenderer

- (id) init {
    self = [super init];
    
    if (self) {
        m_renderUnits = [[NSMutableArray alloc] initWithCapacity:10];
    }
    return self;
}

- (void) dealloc {
    
}

- (void) addRenderUnit:(OpenGLRenderUnit *)renderUnit {
    [m_renderUnits addObject:renderUnit];
}

- (void) render {
    for(OpenGLRenderUnit* renderUnit in m_renderUnits) {
        [renderUnit render];
    }
}

@end
