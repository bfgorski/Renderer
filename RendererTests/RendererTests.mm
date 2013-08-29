//
//  RendererTests.m
//  RendererTests
//
//  Created by Benjamin Gregorski on 1/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "RendererTests.h"
#import "../Framework/FrameBuffer.h"
#import "../UnitTest/Framework/FrameBufferTest.h"

@implementation RendererTests
{
    FrameBufferTest * m_fbTest;
}
- (void)setUp
{
    [super setUp];
    
    // Set-up code here.
}

- (void)tearDown
{
    // Tear-down code here.
    
    [super tearDown];
}

- (void)testFrameBuffer
{
    //STFail(@"Unit tests are not implemented yet in RendererTests");
    //FrameBufferTest * fbt = [FrameBufferTest alloc];
    FrameBuffer *fb = [FrameBuffer alloc];
    [fb init:1024 height:768];
    
    m_fbTest = [FrameBufferTest alloc];
    [m_fbTest testFrameBuffer];
    //STAssertEquals(fb.m_width, 1024, @"Width Not Properly Set");
}

- (void) testRenderer
{
    
}

@end
