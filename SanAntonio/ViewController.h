//
//  ViewController.h
//  SanAntonio
//
//  Created by Benjamin Gregorski on 9/7/13.
//
//

#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>

@class Camera;

@interface ViewController : GLKViewController

@property (weak, nonatomic) IBOutlet UIButton *renderViewButton;
@property (weak, nonatomic) IBOutlet UIButton *optionsButton;

- (IBAction)renderViewButtonPressed:(id)sender;
- (IBAction)optionsButtonPressed:(UIButton *)sender;

@end
