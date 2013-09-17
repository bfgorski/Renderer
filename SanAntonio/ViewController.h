//
//  ViewController.h
//  SanAntonio
//
//  Created by Benjamin Gregorski on 9/7/13.
//
//

#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>

@interface ViewController : GLKViewController
@property (weak, nonatomic) IBOutlet UIButton *renderViewButton;
- (IBAction)renderViewButtonPressed:(id)sender;

@end
