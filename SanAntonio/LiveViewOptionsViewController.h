//
//  LiveViewOptionsViewController.h
//  Renderer
//
//  Created by Benjamin Gregorski on 10/4/13.
//
//

#import <UIKit/UIKit.h>

@interface LiveViewOptionsViewController : UIViewController
@property (weak, nonatomic) IBOutlet UISwitch *showTrackballBoundsSwitch;
- (IBAction)showTrackballBounds:(id)sender forEvent:(UIEvent *)event;

@end
