//
//  AppDelegate.h
//  Trinidad
//
//  Created by Benjamin Gregorski on 9/6/13.
//
//

#import <Cocoa/Cocoa.h>

@interface AppDelegate : NSObject <NSApplicationDelegate>

@property (assign) IBOutlet NSWindow *window;

- (IBAction)renderScene:(id)sender;
- (IBAction)exit:(id)sender;

@property (unsafe_unretained) IBOutlet NSViewController *viewController;
@property (weak) IBOutlet NSImageView *imageView;

@end
