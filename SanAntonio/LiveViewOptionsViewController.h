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

- (IBAction)showTrackballBounds:(UISwitch*)sender forEvent:(UIEvent *)event;

@end
