//
//  AppDelegate.m
//  Trinidad
//
//  Created by Benjamin Gregorski on 9/6/13.
//
//

#import "AppDelegate.h"
#include "Renderer.h"

@implementation AppDelegate
{
    Renderer * m_renderer;
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    // Insert code here to initialize your application
   //NSView * contentView = [self.window contentView];
   
    m_renderer = [[Renderer alloc] init:@"Trinidad"];
}

- (IBAction)renderScene:(id)sender {
    NSDictionary *options = @{
        @"saveFile" : @"/Users/bfgorski/image.png"
    };
    [m_renderer render:options];
    
    NSImage *image = [[NSImage alloc] initWithContentsOfFile:options[@"saveFile"]];
    [self.imageView setImage:image];
}

- (IBAction)exit:(id)sender {
    exit(0);
}

@end
