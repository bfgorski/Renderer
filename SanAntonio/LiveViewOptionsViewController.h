//
//  LiveViewOptionsViewController.h
//  Renderer
//
//  Created by Benjamin Gregorski on 10/4/13.
//
//

#import <UIKit/UIKit.h>
#import "LiveViewOptions.h"

@interface LiveViewOptionsViewController : UIViewController

@property (strong, nonatomic) LiveViewOptions *liveViewOptions;

@property (weak, nonatomic) IBOutlet UISwitch *showTrackballBoundsSwitch;
@property (weak, nonatomic) IBOutlet UISwitch *drawWireframeSwitch;

- (IBAction)showTrackballBounds:(UISwitch*)sender forEvent:(UIEvent *)event;
- (IBAction)showWireframe:(UISwitch*)sender forEvent:(UIEvent *)event;

@end
